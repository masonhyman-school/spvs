#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>

using namespace std;
struct sockaddr_in dest;

int main()
{
   int sockt, connct, port;

   cout << "Enter the number of port: ";
   cin >> port;

   
   if ((sockt = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
      perror("socket");
      exit(1);
   }

   dest.sin_family = AF_INET;
   dest.sin_port = htons(port);
   bzero(dest.sin_zero, sizeof(dest.sin_zero));

   
   if ((connct = connect(sockt, (struct sockaddr *)&dest, sizeof(dest))) == -1) {
      perror("connect");
      close(sockt);
      exit(1);
   } else {
      cout << port << " open" << endl;
      exit(1);
   }

   return 0;
}