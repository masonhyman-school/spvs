/* port_scanner.cpp
 * Ankit Mistry
 * Last Updated October 27, 2022 08:08 PM
 * Originally created by Mason Hyman, modified by me.
 * 
 * Scans for open ports on a given IP address or web address. Works on both stdin and file read.
*/

#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <thread>
#include <SFML/Network.hpp>

using namespace std;

void print_usage() {
	cerr <<  "Usage: spvs [Options] {target specification}" << endl
		  << "TARGET SPECIFICATION:" << endl
		  << "    -f <input file name>: Input from list of hosts." << endl;
}

static bool port_is_open(const string& address, int port) {
	return (sf::TcpSocket().connect(sf::IpAddress::resolve(address).value(), port, sf::milliseconds(100)) == sf::Socket::Status::Done);
}

void threaded_port_is_open(const string& address, int port, vector<bool>& status) {
	cout << address << endl;	
	if(sf::TcpSocket().connect(sf::IpAddress::resolve(address).value(), port) == sf::Socket::Status::Done) {
		status.at(port) = 1;
	}
}

void port_scan(const string& address, int ports) {
	vector <bool> open_ports(ports+1, false);
	vector <thread *> threads;

	bool host_online = false;
	
	for (int i = 1; i <= ports; i++) {
		if (port_is_open(address, i)) {
			host_online = true;
			open_ports.at(i) = true;
			cout << "PORT " << i << " IS OPEN\n";
		} 	
	}

	if (host_online) {
		cout << address << " is ONLINE with open ports: " << endl;
		for (int i = 1; i < open_ports.size(); i++) {
			if (open_ports.at(i)) cout << "   Port " << i << " is open" << endl;
		}
     	cout << endl;
	} else {
		cout << address << " is OFFLINE." << endl;
	}
}

int main(int argc, char ** argv) {
		
	list<string> hosts;
	list<string>::iterator lit;
   string host;
   ifstream file;

	/* PARSE USER COMMANDS */
	if (argc == 1) { print_usage(); return 1; }	
	else if (argc == 2) {
		/* If only two arguments, second arg must be a hostname */
		hosts.push_back(argv[1]);
	}
	else if (argc == 3) {
		if (string(argv[1]) == "-f") {
			/* READ HOSTS FROM FILE */
         file.open(argv[2]);
			if(!file.is_open()) cerr << "Could not open file " << argv[1] << endl;
				
			while (file >> host) hosts.push_back(host); 
			file.close();
			cout << "Successfully read in " << hosts.size() << " hosts" << endl;
		}
	} 

	/* PERFORM BASIC DISCOVERY */
	/* Essentially determining if host is online */
	for (lit = hosts.begin(); lit != hosts.end(); lit++) {
		port_scan(*lit, 65535);
   }

	return 0;
} 
