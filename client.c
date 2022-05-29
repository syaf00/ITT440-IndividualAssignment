#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>  //inet_addr
#include <string.h>
#include <unistd.h>

int main(int argc , char *argv[])
{
        int socket_desc;
        struct sockaddr_in server;
        char *message , server_reply[2000];

        //Creating the socket
        socket_desc = socket(AF_INET , SOCK_STREAM , 0);
        if (socket_desc == -1)
        {
                printf("Could not create socket");
        }

        server.sin_addr.s_addr = inet_addr("192.168.56.104"); //Server VM IP Address
        server.sin_family = AF_INET;
        server.sin_port = htons( 22 );

        //Connecting to remote server
        if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
        {
                puts("Connecting error");
                return 1;
        }

        puts("Connected \n");

        //Send some data
        message = "connect";
        if( send(socket_desc , message , strlen(message) , 0) < 0)
        {
                puts("Sending failed");
                return 1;
        }
        puts("Data has been sent\n");
        
        //Receive a reply from the server
        if( recv(socket_desc, server_reply , 2000 , 0) < 0)
        {
                puts("Receiving failed");
        }
        puts("Reply has been received\n");
        puts(server_reply);
        
        close(socket_desc);     //close socket descriptor

        return 0;
  
}

