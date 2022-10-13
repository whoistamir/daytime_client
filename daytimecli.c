#include "stdio.h"
#include "stdlib.h"
#include <unistd.h>
#include <strings.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define SA struct sockaddr
#define BUFFER_SIZE 4096


int main(int argc, char **argv){
	
	if(argc != 2){
		fprintf(stdout, "usage: daytimecli [ip address]\n");
		exit(EXIT_FAILURE);
	}
	
	// Create socket and check if socket function was executed correctly
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	if(sockfd < 0){
		fprintf(stdout, "warning: socket error\n");
		exit(EXIT_FAILURE);
	}
	
	//Clear server address struct and set server address properties
	struct sockaddr_in servaddr;
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(13);
	
	if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0){
		fprintf(stdout, "warning: could not convert %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}


	
	if(connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0){
		fprintf(stdout, "warning: could not connect to IP address\n");
		exit(EXIT_FAILURE);
	}
	
	char buffer[BUFFER_SIZE + 1];
	int n;
	
	while((n = read(sockfd, buffer, BUFFER_SIZE)) > 0){
		buffer[n] = 0; //null terminator
		write(1, buffer, n);
	}
	
	if(n < 0){
		fprintf(stdout, "warning: read error\n");
		exit(EXIT_FAILURE);
	} 

	close(sockfd);
	exit(EXIT_SUCCESS);
}
