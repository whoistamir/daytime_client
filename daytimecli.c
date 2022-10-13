#include "stdio.h"
#include "stdlib.h"
#include <unistd.h>
#include <strings.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define SA struct sockaddr
#define BUFFER_SIZE 4096


int main(int argc, char **argv){
	
	//Checking command line arguments 
	if(argc != 2){
		fprintf(stdout, "usage: daytimecli [ip address]\n");
		exit(EXIT_FAILURE);
	}
	
	// Create socket and check if socket function does not return error code
	// AF_INET = IPv4 address
	// SOCK_STREAM = TCP/IP
	// last parameter = Leave protocol decision to service provider
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0){
		fprintf(stdout, "warning: socket error\n");
		exit(EXIT_FAILURE);
	}
	
	//Define socket address struct used to initiate connection
	struct sockaddr_in servaddr;
	
	//Clear out socket address struct
	bzero(&servaddr, sizeof(servaddr));

	//Set family of server address struct to IPv4
	servaddr.sin_family = AF_INET;

	//Set port of server address struct to 13 (daytime server)
	servaddr.sin_port = htons(13);
	
	//Convert command line argument from IPv4 address to binary form
	//AF_INET = IPv4 address type
	//argv[1] = source of IP address (command line)
	// &servaddr.sin_addr = destination for converted binary data
	if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0){
		fprintf(stdout, "warning: could not convert %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	//Initiate connection (and check if function returns an err) 
	//with socket file descriptor returned from socket() using
	//data from server address struct
	if(connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0){
		fprintf(stdout, "warning: could not connect to IP address\n");
		exit(EXIT_FAILURE);
	}
	
	//Create buffer and variable to store amount of bytes read
	char buffer[BUFFER_SIZE + 1];
	int n;
	
	//Read from socket until no more data is avaialble, and 
	//write to stdout
	while((n = read(sockfd, buffer, BUFFER_SIZE)) > 0){
		buffer[n] = 0; //null terminator
		write(1, buffer, n);
	}
	
	//Error check read function
	if(n < 0){
		fprintf(stdout, "warning: read error\n");
		exit(EXIT_FAILURE);
	} 

	exit(EXIT_SUCCESS);
}
