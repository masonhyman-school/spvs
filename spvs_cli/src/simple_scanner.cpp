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
        
        //Commonly used top ports
        if(ports[i]==20 || ports[i]==21)
        {
            cout << "Common port: FTP port" << endl;
        }

        else if(ports[i]==22)
        {
            cout << "Common port: SSH port" << endl;
        }

        else if(ports[i]==25)
        {
            cout << "Common port: SMTP port" << endl;
        }

        else if(ports[i]==53)
        {
            cout << "Common port: DNS port" << endl;
        }

        else if(ports[i]==80)
        {
            cout << "Common port: HTTP port" << endl;
        }

        else if(ports[i]==123)
        {
            cout << "Common port: NTP port" << endl;
        }

        else if(ports[i]==179)
        {
           cout << "Common port: BGP port" << endl; 
        }

        else if(ports[i]==443)
        {
            cout << "Common port: HTTPS port" << endl;
        }

        else if(ports[i]==500)
        {
            cout << "Common port: ISAKMP port" << endl;
        }

        else if(ports[i]==3389)
        {
            cout << "Common port: RDP port" << endl;
        }

        if (port_is_open(address, i))
        {
            cout << "OPEN" << endl;
        }

        else
        {
            cout << "CLOSED" << endl;
        }

        cout << endl;
    }
}

int main(int argc, char ** argv)
{
    vector<int> ports;
    int port;
    string address;
    bool rangeScan=false;
    string s;
    int rangeOne;
    int rangeTwo;

    //Address that is used for scanning
    cout << "Please enter address: ";
    getline(cin,address);
    cout << endl;

    //Asking user for scanning range of ports
    cout << "Would you like to scan a range of ports?" << endl;
    cin >> s;
    cout << endl;
   
    if(s=="Yes" || s=="yes")
    {
        rangeScan=true;
    }
    
    //Scanning range of ports
    if(rangeScan)
    {
        cout << "Please enter a range of ports that you would like to scan (ex: 20 40): ";
        cin >> rangeOne >> rangeTwo;
        cout << endl;
        for(int i=rangeOne; i<=rangeTwo; i++)
        {
            ports.push_back(i);
        }
    }

    //Scanning specified ports
    else
    {
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
    }

    scan(address,ports);
   

    return 0;
}

