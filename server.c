#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 8008
int main(int argc, char const *argv[])
{
    int server_d, new_socket;
    long v_read;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // HTTP protocol implementation
    char *aboutme = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 73\n\n Hi my name is Syafiqah and I study Netcentric Computing. What about you?";
  
    // Creating socket file descriptor
    if ((server_d = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("In socket");
        exit(EXIT_FAILURE);
    }


    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    memset(address.sin_zero, '\0', sizeof address.sin_zero);

    //bind
    if (bind(server_d, (struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("In bind");
        exit(EXIT_FAILURE);
    }
        puts("Bind done");

    //listen
    if (listen(server_d, 10) < 0)
    {
        perror("In listen");
        exit(EXIT_FAILURE);
    }
        puts("Listening...");

    //accept incoming connection
    while(1)
    {
        printf("\n==========Waiting for new connection==========\n\n");
        if ((new_socket = accept(server_d, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
        {
            perror("In accept");
            exit(EXIT_FAILURE);
        }

        char buffer[30000] = {0};
        v_read= read( new_socket , buffer, 30000);
        printf("%s\n",buffer );
        write(new_socket , aboutme , strlen(aboutme));
        printf("+++-About Me message sent+++");
        close(new_socket);
    }
    return 0;
}

