#define _CRT_SECURE_NO_WARNINGS
#define PORT 8080

#include <stdio.h>
#include <sys/socket.h> // for connections
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h> // sockaddr_in
#include <string.h>

int main() 
{
    int socket_fd, conn_fd; 
    long valread;
    struct sockaddr_in serveraddr;
    int addrlen = sizeof(serveraddr);
      
    char hello[] = "Server says hello"; // Hello message for communication
    
    // Creating socket
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd == 0)
    {
        perror("In socket");
        exit(EXIT_FAILURE);
    }
    
    serveraddr.sin_family = AF_INET; // Address family
    serveraddr.sin_addr.s_addr = INADDR_ANY; // Any address for binding 0.0.0.0
    serveraddr.sin_port = htons( PORT ); // Defined port 8080
    
    // Bind socket to given IP address
    if (bind(socket_fd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0)
    {
        perror("In bind");
        exit(EXIT_FAILURE);
    }

    // Server is ready to listen, 3 request queued until refused
    if (listen(socket_fd, 3) < 0)
    {
        perror("In listen");
        exit(EXIT_FAILURE);
    }

    // Communication between server and client
    for (;;)
    {
        printf("\nWaiting for new connection\n\n");
        
        // Accept data packets from client
        conn_fd = accept(socket_fd, (struct sockaddr *)&serveraddr, (socklen_t*)&addrlen);
        if (conn_fd < 0)
        {
            perror("In accept");
            exit(EXIT_FAILURE);
        }
        // Hello message sent here
        write(conn_fd , hello , strlen(hello));
        printf("Howdy from server\n");
        close(conn_fd); // close the socket
    }

    return 0;
}