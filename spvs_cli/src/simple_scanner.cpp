#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <SFML/Network.hpp>
#include <sstream>

using namespace std;

static bool port_is_open(const string& address, int port)
{
    return (sf::TcpSocket().connect(sf::IpAddress::resolve(address).value(), port) == sf::Socket::Status::Done);
}

void scan(const string& address, vector<int>ports)
{
    //Scanning each port and seeing whether it is open or closed
    for(int i=0; i<ports.size(); i++)
    {
        cout << "Scanning " << address << "...\n" << "Port " << ports[i] << " : " << endl;
        if (port_is_open(address, i))
        {
            cout << "OPEN" << endl;
        }

        else
        {
            cout << "CLOSED" << endl;
        }
    }
}

int main(int argc, char ** argv)
{
    vector<int> ports;
    int port;
    string address;

    //Address that is used for scanning
    cout << "Please enter address: ";
    getline(cin,address);
    cout << endl;

    cout << "Please enter the ports that you would like to be scanned: " << endl;
    //Getting all the ports that you want to scan
    while(true)
    {
        if(!(cin >> port))
        {
            break;
        }
        ports.push_back(port);
    }
    
    scan(address,ports);

    return 0;
}
