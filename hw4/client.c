#include <arpa/inet.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_STRLEN 256 // The maximum length of key and value strings
#define NUM_SERVER 3

int main(int argc, char *argv[]) {
	int SERVER_PORT[NUM_SERVER] = { 5001, 5002, 5003 };
	/* localhost에서 통신할 것이므로 서버 ip주소도 그냥 localhost */
	const char* server_name = "localhost"; // 127.0.0.1
	struct sockaddr_in srv_addr[NUM_SERVER]; // Create socket structure
	for (int i = 0; i < NUM_SERVER; i++) {
		memset(&srv_addr[i], 0, sizeof(srv_addr[i])); // Initialize memory space with zeros
		srv_addr[i].sin_family = AF_INET; // IPv4
		srv_addr[i].sin_port = htons(SERVER_PORT[i]);
		inet_pton(AF_INET, server_name, &srv_addr[i].sin_addr);  // Convert IP addr. to binary
	}

	int sock[NUM_SERVER];
	for (int i = 0; i < NUM_SERVER; i++) {
		if ((sock[i] = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
			printf("Could not create socket\n");
			exit(1);
		}
	}

	int n = 0;
	int maxlen = 1024;
	char RecvBuffer0[maxlen];
	char RecvBuffer1[maxlen];
	char RecvBuffer2[maxlen];
	char SendBuffer[maxlen];

	struct sockaddr_in cli_addr;
	int cli_addr_len = sizeof(cli_addr);

	while (1) {
		if (fgets(SendBuffer, maxlen, stdin) != NULL) {
			// Parse the received command
			char cmd[MAX_STRLEN] = "", key[MAX_STRLEN] = "", value[MAX_STRLEN] = "", dummy[MAX_STRLEN] = "";
			sscanf(SendBuffer, "%s %s %s %s", cmd, key, value, dummy);

			//Sending the "get" command to all servers
			if(strcmp(cmd, "get") == 0){
				for(int i = 0; i < NUM_SERVER; i++)
					sendto(sock[i], SendBuffer, strlen(SendBuffer), 0, (struct sockaddr*)&srv_addr[i], sizeof(srv_addr[i]));
			}
			else {
				//Do something when received other commands
				continue;
			}
			memset(SendBuffer, 0, maxlen);
		}

		bool serv0Res = false, serv1Res = false, serv2Res = false;
		char printMsg[maxlen];
		sprintf(printMsg, "FALSE");
		while (!serv0Res && !serv1Res && !serv2Res) {
			int n0 = recvfrom(sock[0], &RecvBuffer0, sizeof(RecvBuffer0) - 1, 0, (struct sockaddr*)&cli_addr, &cli_addr_len);
			int n1 = recvfrom(sock[1], &RecvBuffer1, sizeof(RecvBuffer1) - 1, 0, (struct sockaddr*)&cli_addr, &cli_addr_len);
			int n2 = recvfrom(sock[2], &RecvBuffer2, sizeof(RecvBuffer2) - 1, 0, (struct sockaddr*)&cli_addr, &cli_addr_len);

			if (!serv0Res && n0 > 0) {
				RecvBuffer0[n0] = '\0';
				printf("%s\n", RecvBuffer0);
				serv0Res = true;
			}
			if (!serv1Res && n1 > 0) {
				RecvBuffer1[n1] = '\0';
				printf("%s\n", RecvBuffer1);
				serv1Res = true;
			}
			if (!serv2Res && n2 > 0) {
				RecvBuffer2[n2] = '\0';
				printf("%s\n", RecvBuffer2);
				serv2Res = true;
			}

			if ((serv0Res && serv1Res && strcmp(RecvBuffer0, RecvBuffer1) == 0) || (serv1Res && serv2Res && strcmp(RecvBuffer1, RecvBuffer2) == 0) || (serv0Res && serv2Res && strcmp(RecvBuffer0, RecvBuffer2) == 0)) {
				strcpy(printMsg, "TRUE");
				break;
			}
		}

		printf("%s\n",printMsg);

		memset(RecvBuffer0, 0, maxlen);
		memset(RecvBuffer1, 0, maxlen);
		memset(RecvBuffer2, 0, maxlen);
	}

	for(int i = 0; i < NUM_SERVER; i++)
		close(sock[i]);
	return 0;
}