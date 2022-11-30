#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINELEN 50

void PrintUsage() {
	printf("Usage: [COMMAND] {ARGUMENT}\n");
	printf("AVAILABLE COMMANDS: \n");
	printf("   set - sets a specfic field.\n");
	printf("   example {tcp | ip} - shows example headers\n");
}

void PrintTCP(int example) {
	if (example) {
		/* Print the example TCP header */
		printf("<--------------------------------- 32 Bits ------------------------------->\n");
		printf("|-------------------------------------------------------------------------|\n");
		printf("|            Source Port               |         Destination Port         |\n");
		printf("|-------------------------------------------------------------------------|\n");
		printf("|                             Sequence Number                             |\n");
		printf("|-------------------------------------------------------------------------|\n");
		printf("|                          Acknowledgement Number                         |\n");
		printf("|-------------------------------------------------------------------------|\n");
		printf("|   Data   |               |U|A|P|R|S|F|                                  |\n");
		printf("|  Offset  |    Reserved   |R|C|S|S|Y|I|            Window Size           |\n");
		printf("|          |               |G|K|H|T|N|N|                                  |\n");
		printf("|-------------------------------------------------------------------------|\n");
		printf("|              Checksum                |           Urgent Pointer         |\n");
		printf("|-------------------------------------------------------------------------| __\n");
		printf("|                                                                         | |\n");
		printf("|                                                                         | |\n");
		printf("|                                   Options                               | 40 Bytes\n");
		printf("|                                                                         | |\n");
		printf("|                                                                         | |\n");
		printf("|-------------------------------------------------------------------------| __\n");
		printf("|                                                                         |\n");
		printf("|                                                                         |\n");
		printf("|                                    Data                                 |\n");
		printf("|                                                                         |\n");
		printf("|                                                                         |\n");
		printf("|-------------------------------------------------------------------------|\n");
	} else {
		// Print current TCP header.
	}
}

void PrintIP(int example) {
	if(example) {
		/* Print the example IP header */
		printf("<--------------------------------- 32 Bits ------------------------------->\n");
		printf("|-------------------------------------------------------------------------| __\n");
		printf("| Version |   IHL   |       TOS        |            Total Length          | |\n");
		printf("|-------------------------------------------------------------------------| |\n");
		printf("|             Identification           |  Flags  |     Fragment Offset    | |\n");
		printf("|-------------------------------------------------------------------------| 20 Bytes\n");
		printf("|       TTL         |     Protocol     |          Header Checksum         | |\n");
		printf("|-------------------------------------------------------------------------| |\n");
		printf("|                               Source Addresss                           | |\n");
		printf("|-------------------------------------------------------------------------| |\n");
		printf("|                             Destination Addresss                        | |\n");
		printf("|-------------------------------------------------------------------------| __\n");
		printf("|                                                                         | |\n");
		printf("|                                                                         | |\n");
		printf("|                                   Options                               | 40 Bytes\n");
		printf("|                                                                         | |\n");
		printf("|                                                                         | |\n");
		printf("|-------------------------------------------------------------------------| __\n");
		printf("|                                                                         | |\n");
		printf("|                                                                         | |\n");
		printf("|                                     Data                                | Up to 65515 Bytes\n");
		printf("|                                                                         | |\n");
		printf("|                                                                         | |\n");
		printf("|-------------------------------------------------------------------------| __\n");
	} else {
		// Print current IP header.
	}
}

int main() {
	printf("Welcome to pktbldr 1.0, a tool to build custom raw TCP/IP packets.\n");
	printf("To see usage type 'help' or 'h'\n\n");	

	char * input = (char *)malloc(MAXLINELEN * sizeof(char));
	while(1) {
		/* Print prompt */
		printf("pktbldr >>> ");
		
		if (fgets(input, MAXLINELEN, stdin) == NULL) {
			continue;
		}
		
		input[strlen(input) - 1] = '\0';

		/* Main input switch */
		char * command = strtok(input, " ");
		if (!strcmp(command, "help") || !strcmp(command, "h")) {
			PrintUsage();
		} 
		else if (!strcmp(command, "example")) {
			char * argument = strtok(NULL, " ");
			if (!strcmp(argument, "tcp")) {
				PrintTCP(1);
			}
			else if (!strcmp(argument, "ip")) {
				PrintIP(1);
			}
		} else if (!strcmp(command, "quit") || !strcmp(command, "exit")) {
			break;
		} else {
			fprintf(stderr, "Invalid input. Type 'help' or 'h' to see commands.\n");
			continue;
		}
	}

	/* Free memory */
	free(input);
}
