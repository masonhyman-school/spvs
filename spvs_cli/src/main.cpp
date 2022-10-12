#include <iostream>
#include <SFML/Network.hpp>

using namespace std;

static bool port_is_open(const string& address, int port) {
	sf::IpAddress addr(127, 0, 0, 1);
	return (sf::TcpSocket().connect(addr, port) == sf::Socket::Status::Done);
}

int main(int argc, char ** argv) {
	cout << "Port 1947 : ";
	if (port_is_open("localhost", 1947)) cout << "OPEN" << endl;
	else cout << "CLOSED" << endl;

	return 0;
} 
