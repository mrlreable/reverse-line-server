#include <stdio.h>
#include <winsock2.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1000
#define PORT 8080
#define SA struct sockaddr
#pragma comment(lib,"libws2_32.a")//Winsock Library

//build: gcc client.c -o client -lws2_32

//need to initialize winsock here as well
void initWinSock(){
    WSADATA wsa;
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		printf("Failed. Error Code : %d",WSAGetLastError());

	}

	printf("Initialized.\n");
}
void func(int sockfd)
{
    char buff[MAX];
    int n;
    for (;;) {
        bzero(buff, sizeof(buff));
        printf("Enter a line: ");
        n = 0;
        while ((buff[n++] = getchar()) != '\n')
            ;
        //write(sockfd, buff, sizeof(buff)); <-
        send(sockfd, buff, sizeof(buff), 0);
        bzero(buff, sizeof(buff));
        //read(sockfd, buff, sizeof(buff)); <-
        recv(sockfd, buff, sizeof(buff), 0);
        printf("From Server : %s", buff);
        if (strncmp(buff, "exit", 4) == 0) {
            printf("Client Exit...\n");
            break;
        }
    }
}

int main()
{
    //initializing winsock
    initWinSock();

    int sockfd, connfd;
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
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    // connect the client socket to server socket
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        printf("connection with the server failed...\n");
        exit(0);
    }
    else
        printf("connected to the server..\n");

    // function for chat
    func(sockfd);

    // close the socket
    close(sockfd);
}
