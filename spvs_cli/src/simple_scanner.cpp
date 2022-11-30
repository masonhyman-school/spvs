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

        else if(ports[i]==23)
        {
            cout << "Common port: Telnet" << endl;
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

        else if(ports[i]==110)
        {
            cout << "Common port: Pop3" << endl;
        }

        else if(ports[i]==123)
        {
            cout << "Common port: NTP port" << endl;
        }

        else if(ports[i]==137)
        {
            cout << "Common port: NetBois port" << endl;
        }

        else if(ports[i]==143)
        {
            cout << "Common port: IMAP port" << endl;
        }

        else if(ports[i]==161)
        {
            cout << "Common port: SNMP" << endl;
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
    vector<string>addresses;
    int port;
    string address;
    bool rangeScan=false;
    string s;
    string st;
    string stri;
    string x;
    bool defaultScan=false;
    int rangeOne;
    int rangeTwo;
    bool IPScan=false;
    
    cout << "Would you like to do a default scan?";
    cin >> x;
    cout << endl;

    if(x=="Yes" || x=="yes")
    {
        defaultScan=true;
    }

    //Default scan: scanning first 100 ports for "localhost" address
    if(defaultScan)
    {
        for(int i=0; i<=100; i++)
        {
            ports.push_back(i);
        }

        scan("localhost",ports);
    }

    else
    {
        cout << "Would you like to scan for multiple addresses?" << endl;
        cin >> st;
        cout << endl;

        if(st=="Yes" || st=="yes")
        {
            IPScan=true;
        }

        if(IPScan)
        {
            //Scanning multiple addresses if user specifies
            cout << "Please enter the addresses that you would like to use: " << endl;

            //Reading in addresses until user "quits"
            while(true)
            {
                cin >> stri;
                if(stri=="q")
                {
                    break;
                }

                addresses.push_back(stri);
            }
        } 

        else
        {
            //Single address that is used for scanning
            cout << "Please enter address: " << endl;
            cin >> address;
            addresses.push_back(address);
            cout << endl;
        }

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

        //Scanning all ports for each address
        for(int i=0; i<addresses.size(); i++)
        {
            scan(addresses[i],ports);
        }
    }
    
   
    return 0;
}

