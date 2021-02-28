#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#define MAX 1000
#define PORT 8080
#define SA struct sockaddr


// Function for chat between server and client
void chat(int sockfd){
    char buff[MAX];
    int i, j, temp;
    // infinite loop for chat
    for (;;){
        bzero(buff, MAX);

        // read the message from client and copy it in buffer
        read(sockfd, buff, sizeof(buff));

        // print buffer which contains the client contents
        printf("From client: %s\t To client : ", buff);

        // create server message by reversing the string from client (->buff)
        for(i = 0, j = strlen(buff) - 1; i < j; i++, j--){
            temp = buff[i];
            buff[i] = buff[j];
            buff[j] = temp;
        }

        write(sockfd, buff, sizeof(buff));

        // if msg contains "exit" then server exit and chat ended.
        if (strncmp("exit", buff, 4) == 0) {
            printf("Server Exit...\n");
            break;
        }
    }
}
int main()
{
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;

    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("Socket creation failed.\n");
        exit(0);
    }
    else
        printf("Socket successfully created.\n");
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    // Binding newly created socket to given IP and verification
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
        printf("Socket bind failed.\n");
        exit(0);
    }
    else
        printf("Socket successfully binded.\n");

    // Now server is ready to listen and verification
    if ((listen(sockfd, 5)) != 0) {
        printf("Listen failed.\n");
        exit(0);
    }
    else
        printf("Server listening.\n");
    len = sizeof(cli);

    // Accept the data packet from client and verification
    connfd = accept(sockfd, (SA*)&cli, &len);
    if (connfd < 0) {
        printf("Server accept failed.\n");
        exit(0);
    }
    else
        printf("Server accepted the client.\n");

    // Function for chatting between client and server
    chat(connfd);

    // After chatting close the socket
    close(sockfd);

    return 0;
}
