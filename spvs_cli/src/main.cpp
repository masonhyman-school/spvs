#include <iostream>
#include <fstream>
#include <cstdlib>
#include <list>
#include <algorithm>
#include <thread>
#include <mutex>
#include <chrono>
#include <ctime>
#include <locale>
#include <SFML/Network.hpp>

#include "spvs.h"

using namespace std;

std::mutex m;

int main(int argc, char** argv) {
/*	Target t;
	if (t.ICMP_Host_Online(argv[1])) cout << "Host is online" << endl;
	else cout << "Something wrong" << endl;

	vector<int> ports;
	for (int i = 1; i < 65000; i++) {
		ports.push_back(i);
	}
	t.TCP_Scan_Ports(argv[1], ports);
	
	t.TCP_Print_Open_Ports();

	if (argc == 1) {
		Print_Usage();
		exit(1);
	}

	Input input(argc, argv);
	if (input.Arg_Exists("-f")) cout << "Found" << endl;

	cout << input.Get_Next_Arg("-f") << endl;
*/
	SPVS(argc, argv);
	return 0;
}




/* DEFINITIONS FOR spvs.h */

/* SPVS CLASS */

/*
 * @name SPVS
 * @brief Constructor for SPVS class. Serves as driver for program.
 * @param[in] argc - number of args on stdin
 * @param[in] argv - array of args from stdin
 * @return SPVS class
 */

SPVS::SPVS(int &argc, char ** argv) {
	vector <Target *> tmp;

	if (argc == 1) Print_Usage();
	
	/* Begin timing information */
	auto start = chrono::system_clock::to_time_t(chrono::system_clock::now());
	cout << "Starting SPVS at " << ctime(&start); 
	
	this->input = new Input(argc, argv);
	
	/* Check to see if -f has been specified, if so handle the file and load targets */
	if (this->input->Arg_Exists("-f")) {
		this->targets = this->input->Get_Targets_From_File(this->input->Get_Next_Arg("-f"));
	}

	/* Check to see if -p has been specified, if so load port / port range */
	if (this->input->Arg_Exists("-p")) {
		this->ports_to_scan = this->input->Get_Ports_To_Scan(this->input->Get_Next_Arg("-p"));		
	} else {
		/* No ports specified, populate default */
		/* TODO */
	}
	
	/* Treat all words on stdin without '-' or '--' as targets */
	tmp = this->input->Get_Targets_From_Stdin();
	targets.insert(targets.end(), tmp.begin(), tmp.end());

	/* Once targets have been gathered, identify modifers to default SPVS */
		

	/* End timing and print results */
	auto end = chrono::system_clock::to_time_t(chrono::system_clock::now());
//	Print_Targets();
//	Print_Ports();
}

/*
 *	@name Print_Usage
 *	@brief Prints spvs usage.
 */
void SPVS::Print_Usage() {	
	cerr <<  "Usage: spvs [Options] {target specification}" << endl
		 << "TARGET SPECIFICATION:" << endl
		 << "    -f <input file name>: Input from list of hosts." << endl;

	exit(1);
}

void SPVS::Print_Targets() {
	for (int i = 0; i < targets.size(); i++) {
		cout << targets[i]->Get_Address() << endl;
	}
}

void SPVS::Print_Ports() {
	for (int i = 0; i < ports_to_scan.size(); i++) {
		cout << ports_to_scan[i] << " ";
	}
	cout << endl;
}







/* INPUT CLASS */

/*
 *	@name Input
 *  @brief Constructor for the Input class, adds argv to args vector in class instance.
 *  @param[in] argc - number of arguments
 *  @param[in] argv - array of command line arguments.
 *  @return Input class instance.
 */
Input::Input(int &argc, char ** argv) {
	for (int i = 1; i < argc; i++) {
		this->args.push_back(string(argv[i]));
	}
}

/*
 *	@name Arg_Exists
 *	@brief Checks if supplied argument exists in user's input
 *	@param[in] option - supplied argument to find
 *  @return true if arg was found
 */

bool Input::Arg_Exists(const string& option) const {
	return find(args.begin(), args.end(), option) != args.end();
}

/*
 *	@name Get_Next_Arg
 *	@brief return argument following supplied option
 *	@param[in] option
 *  @return the desired argument, empty string if none exists
 */

const string& Input::Get_Next_Arg(const string& option) const {
	list<string>::const_iterator lit;

	/* Find the supplied argument and then return the following argument */
	lit = find(args.begin(), args.end(), option);
	
	if (lit != args.end() && ++lit != args.end()) {
		return *lit;
	} 

	static const string empty = "";	
	return empty;
}

/* 
 *	@name Get_Targets_From_File
 *	@brief Collects all words from file and initializes Target instance for each.
 *	@param[in] filename - target filename
 *  @return vector<Target *> - list of targets to be assigned to SPVS class.
 */

vector<Target *> Input::Get_Targets_From_File(const string& filename) {
	vector<Target *> ret;
	string s;
	ifstream file;
	Target * t;

	file.open(filename);

	if (!file.is_open()) {
		cerr << endl << "ERROR: Could not open file: " << filename << endl;
		exit(1);
	}

	while(file >> s) {
		t = new Target(s);
		ret.push_back(t);
	}	

	/* Cleanup and remove -f and filename from args */
	file.close();	
	
	args.erase(find(args.begin(), args.end(), "-f"));	
	args.erase(find(args.begin(), args.end(), filename));	
	return ret;	
}

/* 
 *	@name Get_Targets_From_Stdin
 *	@brief Collects all non '-' or '--' args and creats targets for them.
 *	@return a vector of targets to be assigned to SPVS class.
 *
 */

vector<Target *> Input::Get_Targets_From_Stdin() {
	list<string>::const_iterator lit;
	vector<Target *> ret;
	Target * t;

	for (lit = args.begin(); lit !=  args.end(); lit++) {
		if (lit->at(0) != '-') {
			string name = *lit;
			t = new Target(name);
			ret.push_back(t);
		} 
	}

	return ret;
}

vector<int> Input::Get_Ports_To_Scan(const string& input) {
	vector<int> ret;

	/* Check to see if range was specified */
	int pos = input.find('-');
	if (pos != string::npos) {
		/* Split the string */
		string l;
		for (int i = 0; i < pos; i++) l += input[i];

		string r;
		for (int i = pos + 1; i < input.size(); i++) r += input[i];
		
		if (!all_of(l.begin(), l.end(), ::isdigit) || !all_of(r.begin(), r.end(), ::isdigit)) {
			cerr << endl << "ERROR: Invalid port specified, must be a number" << endl;
			exit(1);
		}

		int starting_port = stoi(l);
		int ending_port = stoi(r);
		
		if (starting_port >= ending_port) {
			cerr << endl << "ERROR: Starting port must not be greater than ending port" << endl;
			exit(1);
		} else if (ending_port > 65535 || starting_port < 1) {
			cerr << endl << "ERROR: Port specification out of bounds. Port range must be between 1 - 65535" << endl;
			exit(1);
		}

		for (int i = starting_port; i <= ending_port; i++) {
			ret.push_back(i);
		}
	} else {
		/* Only one port specified */
		if (!all_of(input.begin(), input.end(), ::isdigit)) {
			cerr << endl << "ERROR: Invalid port specified, must be a number" << endl;
			exit(1);
		}
		
		int port = stoi(input);
	
		if (port < 1 || port > 65535) {
			cerr << endl << "ERROR: Port specification out of bounds. Port range must be between 1 - 65535" << endl;
			exit(1);
		}

		ret.push_back(port);
	}
		
	/* Cleanup and remove -p and port specification from args */
	args.erase(find(args.begin(), args.end(), "-p"));	
	args.erase(find(args.begin(), args.end(), input));	
	return ret;
}








/* TARGET CLASS */

/*
 *	@name Target
 *	@brief Constructs a Target instance, assignes its address.
 */

Target::Target(string& address) {
	this->address = address;
}

/*
 *	@name Host_Online
 *	@brief returns true if host is online using UNIX ping
 *	@param[in] address - address of target as string
 * 	@return true if host is online false if isn't
 */

bool Target::ICMP_Host_Online(const string& address) {
	string command = "ping -c1 -s1 ";
	command.append(address);
	command.append(" &> /dev/null");
	if (!system(command.c_str())) return true;
	
	return false;
}

/*
 *	@name TCP_Port_Is_Open
 *	@brief Checks if single port is open on target, adds to open_ports if open.
 *	@param[in] address - address of target 
 *	@param[in] port - target port
 *	@return void
 */

void Target::TCP_Port_Is_Open(const string& address, const int port) {
	m.lock();

	if (sf::TcpSocket().connect(sf::IpAddress::resolve(address).value(), port, sf::milliseconds(100)) == sf::Socket::Status::Done) {
		/* If port is open add port to open_ports */
		open_ports.push_back(port);
	}

	m.unlock();
}

/*
 *	@name TCP_Scan_Ports
 *	@brief Scans given ports quickly using multithreading
 *	@param[in] address - address of target
 *	@param[in] ports - list of ports to be scanned.
 */

void Target::TCP_Scan_Ports(const string& address, const vector<int>& ports) {
	vector <thread *> scanning_tasks;

		/* For all ports in ports vector, scan that port */	
		for (int i = 0; i < ports.size(); i++) {
			/* Push port scan to thread */
			scanning_tasks.push_back(new thread(&Target::TCP_Port_Is_Open, this, address, ports[i]));
			
			/* Only create 50 threads at a time as to avoid maxing out threads */
			if (i % 50 == 0 && i != 0) {
				
				for (int j = 0; j < scanning_tasks.size(); j++) {
					scanning_tasks[j]->join();
					delete scanning_tasks[j];
				}
				
				scanning_tasks.clear();
			}
		}
}

/*
 *	@name TCP_Print_Open_Ports
 *	@brief Sorts the open_ports vector and prints to user.
 */

void Target::TCP_Print_Open_Ports() {
	sort(open_ports.begin(), open_ports.end());
	for (int i = 0; i < open_ports.size(); i++) cout << open_ports[i] << endl;
}

/*
 *	@name Get_Address 
 *	@brief Accessor function for targets address.
 *  @return Const reference to targets address.
 */

const string& Target::Get_Address() {
	return address;
} 
