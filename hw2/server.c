#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_PAIRS 10000 // The maximum number of key-value pairs
#define MAX_STRLEN 256 // The maximum length of key and value strings

/* KVS structure */
typedef struct {
    char key[MAX_STRLEN];
    char value[MAX_STRLEN];
} KeyValuePair;

KeyValuePair kv_store[MAX_PAIRS];
int kv_count = 0;

// Function to put a key-value pair into the dictionary
void put(const char *key, const char *value) {
    int i;
    for (i = 0; i < kv_count; i++) {
        if (strcmp(kv_store[i].key, key) == 0) {
            strcpy(kv_store[i].value, value);
            return;
        }
    }

    if (kv_count < MAX_PAIRS) {
        strcpy(kv_store[kv_count].key, key);
        strcpy(kv_store[kv_count].value, value);
        kv_count++;
    }
}

// Function to get the value for a key from the dictionary
const char *get(const char *key) {
    int i;
    for (i = 0; i < kv_count; i++) {
        if (strcmp(kv_store[i].key, key) == 0) {
            return kv_store[i].value;
        }
    }
    return NULL;
}



int main(int argc, char *argv[]) {
	if ( argc < 2 ){
	 printf("Input : %s port number\n", argv[0]);
	 return 1;
	}

	int SERVER_PORT = atoi(argv[1]);

	struct sockaddr_in srv_addr;
	memset(&srv_addr, 0, sizeof(srv_addr));
	srv_addr.sin_family = AF_INET;
	srv_addr.sin_port = htons(SERVER_PORT);
	srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	int sock;
	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		printf("Could not create listen socket\n");
		exit(1);
	}

	if ((bind(sock, (struct sockaddr *)&srv_addr, sizeof(srv_addr))) < 0) {
		printf("Could not bind socket\n");
		exit(1);
	}


	struct sockaddr_in cli_addr;
    int cli_addr_len = sizeof(cli_addr);

	int  maxlen = 1024;
	int n = 0;
	char RecvBuffer[maxlen];
    char SendBuffer[maxlen];

    while (1) {
        n = recvfrom(sock, &RecvBuffer, sizeof(RecvBuffer), 0, (struct sockaddr *)&cli_addr, &cli_addr_len);
        if (n > 0) {
            /* Please add your codes here!!! */
            RecvBuffer[n] = '\0'; // null terminate the received buffer

           // Parse the received command
           char cmd[MAX_STRLEN] ="", key[MAX_STRLEN] = "", value[MAX_STRLEN] = "", dummy[MAX_STRLEN] = "";
           sscanf(RecvBuffer, "%s %s %s %s", cmd, key, value, dummy);
           printf("%s", RecvBuffer);

           if ((strcmp(cmd, "get") == 0) && (strcmp(key, "") != 0) && (strcmp(value, "") == 0) && (strcmp(dummy, "") == 0)) {
               const char* findValue = get(key);
               if (findValue != NULL) {
                   sprintf(SendBuffer, "%s", findValue);
               }
               else {
                   sprintf(SendBuffer, "Key not found");
               }
           }

           else if ((strcmp(cmd, "put") == 0) && (strcmp(key, "") != 0) && (strcmp(value, "") != 0) && (strcmp(dummy, "") == 0)) {
               put(key, value);
               sprintf(SendBuffer, "OK");
           }
           else {
               sprintf(SendBuffer, "Invalid command");
           }

           printf("%s\n", SendBuffer);
           sendto(sock, &SendBuffer, sizeof(SendBuffer), 0, (struct sockaddr*)&(cli_addr), sizeof(cli_addr));
          }
      }
    close(sock);

    return 0;
}
