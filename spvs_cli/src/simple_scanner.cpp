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
        cout << "Scanning " << address << "...\n" << "Port " << i << " : " << endl;
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
    ifstream my_file;
    string address;
    int port;
    string s;
    stringstream ss;

    if(argc!=2)
    {
        cerr << "Incorrect number of arguments" << endl;
    }

    else
    {
        my_file.open(argv[1]);
        if(my_file.fail())
        {
            cerr << "Could not open file" << endl;
        }

        //Getting the address
        cout << "Enter Address: ";
        getline(cin, address);
        cout << endl;

        /* Getting all the ports and then scanning each one with associated address */
        while(getline(my_file,s))
        {
            ss.clear();
            ss<<s;
            ss>>port;
            ports.push_back(port);
        }

        scan(address,ports);
    }
    return 0;
}
