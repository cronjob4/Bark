/*
BARK
Client.c
 */
#include <unistd.h>
#include<stdio.h> //printf
#include<string.h>    //strlen
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr
#include<netinet/in.h>
#include "engine.h"

int main(int argc , char *argv[])
{
    int sock;
    struct sockaddr_in server;
    char message[1000] , server_reply[2000];
    
    //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");
    
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons( 8888 );
    
    //Connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return 1;
    }
    
    puts("Connected\n");
    struct diffe_ctx *user;
    init_diffe_ctx(&user);

        if( send(sock, user->A, 256, 0) < 0)
        {
            puts("Send failed");
            return 1;
        }
    
    //keep communicating with server
    while(1)
    {
        printf("Enter message: ");

        //Receive a reply from the server
        if( recv(sock , server_reply , 2000 , 0) < 0)
        {
            puts("recv failed");
            break;
        }
        puts("Server reply :");
        for(int i = 0; server_reply[i] != 0; ++i)
                printf("%02x", server_reply[i]);
        puts(server_reply);
    }
    
    close(sock);
    return 0;
}
