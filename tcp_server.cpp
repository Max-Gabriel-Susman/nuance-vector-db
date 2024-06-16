#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    std::cout << "Serving Nuance Vector Database v0.n.n on port 8080" << std::endl;

    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        std::cerr << "ERROR opening socket" << std::endl;
        return 1;
    }

    // Prepare the sockaddr_in structure
    std::memset((char *) &serv_addr, 0, sizeof(serv_addr));
    portno = 8080;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    // Bind the socket to the address
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "ERROR on binding" << std::endl;
        return 1;
    }

    // Listen for incoming connections
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    // Accept an incoming connection
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if (newsockfd < 0) {
        std::cerr << "ERROR on accept" << std::endl;
        return 1;
    }

    // Read data from the client
    std::memset(buffer, 0, 256);
    n = read(newsockfd, buffer, 255);
    if (n < 0) {
        std::cerr << "ERROR reading from socket" << std::endl;
        return 1;
    }
    std::cout << "Here is the message: " << buffer << std::endl;

    // Send a response to the client
    n = write(newsockfd, "I got your message", 18);
    if (n < 0) {
        std::cerr << "ERROR writing to socket" << std::endl;
        return 1;
    }

    // Close the sockets
    close(newsockfd);
    close(sockfd);
    return 0;
}
