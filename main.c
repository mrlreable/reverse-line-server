#include <stdio.h>
#include <winsock2.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1000
#define PORT 8080
#define SA struct sockaddr
#pragma comment(lib,"libws2_32.a")//Winsock Library

//build: gcc main.c -o main -lws2_32

const char* reverseLine(char line[]){
    char reversedLine[MAX];
    int count, i = 0;
    while(line[count] != '\0'){
        count++;
    }

    for(i = 0; i < count; i++){
        reversedLine[i] = line[count - 1 - i];
    }
    reversedLine[i] = '\0';
    return reversedLine;
}
void initWinSock(){
    WSADATA wsa;
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		printf("Failed. Error Code : %d",WSAGetLastError());

	}

	printf("Initialized.\n");
}
// Function for chat between server and client
void chat(int sockfd){
    char buff[MAX];
    int n;
    // infinite loop for chat
    for (;;) {
        bzero(buff, MAX);

        // read the message from client and copy it in buffer
        //read(sockfd, buff, sizeof(buff)); <-
        recv(sockfd, buff, sizeof(buff), 0);
        // print buffer which contains the client contents
        printf("From client: %s\t To client : ", buff);
        //bzero(buff, MAX); <-
        n = 0;
        // copy server message in the buffer
        //while ((buff[n++] = getchar()) != '\n');

        // and send that buffer to client
        //write(sockfd, reverseLine(buff), sizeof(buff));

        send(sockfd, buff, sizeof(buff), 0);
        //write(sockfd, buff, sizeof(buff));

        // if msg contains "exit" then server exit and chat ended.
        if (strncmp("exit", buff, 4) == 0) {
            printf("Server Exit...\n");
            break;
        }
    }
}
int main()
{
    //initializing winsock
    initWinSock();

    /*char line[MAX];
    printf("Enter a line: ");
    fgets(line, MAX, stdin);

    reverseLine(line);*/

    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;

    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    // Binding newly created socket to given IP and verification
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
        printf("socket bind failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully binded..\n");

    // Now server is ready to listen and verification
    if ((listen(sockfd, 5)) != 0) {
        printf("Listen failed...\n");
        exit(0);
    }
    else
        printf("Server listening..\n");
    len = sizeof(cli);

    // Accept the data packet from client and verification
    connfd = accept(sockfd, (SA*)&cli, &len);
    if (connfd < 0) {
        printf("server acccept failed...\n");
        exit(0);
    }
    else
        printf("server acccept the client...\n");

    // Function for chatting between client and server
    chat(connfd);

    // After chatting close the socket
    close(sockfd);

    return 0;
}
