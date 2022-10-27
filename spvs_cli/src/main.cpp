#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <thread>
#include <mutex>
#include <SFML/Network.hpp>

#include "spvs.h"

using namespace std;

std::mutex m;

int main(int argc, char** argv) {
	Target t;
	if (t.ICMP_Host_Online(argv[1])) cout << "Host is online" << endl;
	else cout << "Something wrong" << endl;

	vector<int> ports;
	for (int i = 1; i < 65000; i++) {
		ports.push_back(i);
	}
	t.TCP_Scan_Ports(argv[1], ports);
	
	t.TCP_Print_Open_Ports();
	return 0;
}





/* DEFINITIONS FOR spvs.h */

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
