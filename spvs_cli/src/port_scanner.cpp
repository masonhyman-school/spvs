/* port_scanner.cpp
 * Ankit Mistry
 * Last Updated October 27, 2022 08:08 PM
 * Originally created by Mason Hyman, modified by me.
 *
 * Scans for open ports on a given IP address or web address. Works on both stdin and file read.
 */

#include <iostream>
#include <sstream>
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
mutex m;

static bool port_is_open(const string &address, int port)
{
    return (sf::TcpSocket().connect(sf::IpAddress::resolve(address).value(), port, sf::milliseconds(100)) == sf::Socket::Status::Done);
}

void threaded_port_is_open(const string &address, int port, vector<bool> &status)
{
    cout << address << endl;
    if (sf::TcpSocket().connect(sf::IpAddress::resolve(address).value(), port) == sf::Socket::Status::Done)
    {
        status.at(port) = 1;
    }
}

void port_scan(const string &address, int ports)
{
    vector<bool> open_ports(ports + 1, false);
    vector<thread *> threads;

    bool host_online = false;

    for (int i = 1; i <= ports; i++)
    {
        if (port_is_open(address, i))
        {
            host_online = true;
            open_ports.at(i) = true;
            cout << "PORT " << i << " IS OPEN\n";
        }
    }

    if (host_online)
    {
        cout << address << " is ONLINE with open ports: " << endl;
        for (int i = 1; i < open_ports.size(); i++)
        {
            if (open_ports.at(i))
                cout << "   Port " << i << " is open" << endl;
        }
        cout << endl;
    }
    else
    {
        cout << address << " is OFFLINE." << endl;
    }
}

int main(int argc, char **argv)
{
    SPVS(argc, argv);
    return 0;
}

/* Code taken from main.cpp */
SPVS::SPVS(int &argc, char **argv) 
{
    vector <Target *> trgts;

    if (argc == 1) {
        cerr << "Usage: spvs [options] {target specification}" << endl
             << "TARGET SPECIFICATION:" << endl
             << "    -f <input file name>: Input from list of hosts." << endl
             << "    -p <port range>: Single port or port range specified start-end." << endl
             << "        Ex: spvs -p 10     Scans only port 10." << endl
             << "        Ex: spvs -p 10-100 Scans only 10 through 100." << endl;
    }

    auto start_time = chrono::system_clock::to_time_t(chrono::system_clock::now());
    cout << "Starting SPVS at " << ctime(&start_time);

    this->input = new Input(argc, argv);
    
    if (this->input->Arg_Exists("-f")) {
        this->targets = this->input->Get_Targets_From_File(this->input->Get_Next_Arg("-f"));
    }

    if (this->input->Arg_Exists("-p")) {
        this->ports_to_scan = this->input->Get_Ports_To_Scan(this->input->Get_Next_Arg("-p"));
        this->services = new Services("references/services");
    } else {
        this->services = new Services("references/top_ports");
    }

    trgts = this->input->Get_Targets_From_Stdin();
    targets.insert(targets.end(), trgts.begin(), trgts.end());

    Scan_Targets();
    Print_Targets();

    auto end_time = chrono::system_clock::to_time_t(chrono::system_clock::now());
    cout << "Successfully completed: " << targets.size() << " hosts scanned " << difftime(end_time, start_time) << " seconds." << endl;
}

void SPVS::Scan_Targets() 
{
    vector <Target *>::const_iterator targetit;
    Target *tmpt;

    for (targetit = targets.begin(); targetit != targets.end(); targetit++) {
        tmpt = *targetit;

        if (!tmpt->ICMP_Host_Online(tmpt->Get_Address())) {
            tmpt->Set_Online(false);
            break;
        }

        tmpt->Set_Online(true);
        tmpt->TCP_Scan_Ports(tmpt->Get_Address(), ports_to_scan);
    }
}