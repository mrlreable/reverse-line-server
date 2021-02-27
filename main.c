#include <stdio.h>
#include <winsock2.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1000
#define PORT 8080
#define SA struct sockaddr
#pragma comment(lib,"libws2_32.a")//Winsock Library

//build: gcc main.c -o main.exe -lws2_32
//run: main.c

void reverseLine(char line[]){
    char reversedLine[MAX];
    int count, i = 0;
    while(line[count] != '\0'){
        count++;
    }

    for(i = 0; i < count; i++){
        reversedLine[i] = line[count - 1 - i];
    }
    reversedLine[i] = '\0';
    printf("%s", reversedLine);
}
void initWinSock(){
    WSADATA wsa;
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		printf("Failed. Error Code : %d",WSAGetLastError());

	}

	printf("Initialized.");
}
void func(int sockfd){
    char buff[MAX];
    int n;
    // infinite loop for chat
    for (;;) {
        bzero(buff, MAX);

        // read the message from client and copy it in buffer
        read(sockfd, buff, sizeof(buff));
        // print buffer which contains the client contents
        printf("From client: %s\t To client : ", buff);
        bzero(buff, MAX);
        n = 0;
        // copy server message in the buffer
        while ((buff[n++] = getchar()) != '\n')
            ;

        // and send that buffer to client
        write(sockfd, buff, sizeof(buff));

        // if msg contains "Exit" then server exit and chat ended.
        if (strncmp("exit", buff, 4) == 0) {
            printf("Server Exit...\n");
            break;
        }
    }
}
int main()
{
    char line[MAX];
    printf("Enter a line: ");
    fgets(line, MAX, stdin);

    //initializing winsock
    initWinSock();

    reverseLine(line);



    return 0;
}
