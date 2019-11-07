///Nichole Boothroyd CMPS109 
#include <vector>
#include <thread>
#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> 
#include <netdb.h>

#include "crack.h"

static void error(std::string msg) {
	std::cout << msg << std::endl;
	exit(-1);
}

int main(int argc, char *argv[]) {

	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) 
		error("sockfd");

	struct sockaddr_in server_addr;
	bzero((char *) &server_addr, sizeof(server_addr) );
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(get_multicast_port()); 

	if( bind(sockfd,(struct sockaddr *) &server_addr, sizeof(server_addr)) <0)
		error("bind");
	
	struct ip_mreq multicastRequest;
	multicastRequest.imr_multiaddr.s_addr = get_multicast_address();
	multicastRequest.imr_interface.s_addr = htonl(INADDR_ANY);

	if( setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void *) &multicastRequest, sizeof(multicastRequest)) <0) 
		error("setsockopt");

	Message msg;
	std::string id = "nboothro";
	std::vector<std::thread*> threads;
	
//	while (true) {
		int n = recvfrom(sockfd, &msg, sizeof(msg), 0, NULL, 0);
		if (n < 0)
			error("recv");
		std::cout<< "Recv Msg" <<std::endl;
		//Recieve no more packets
		//If the UDP packet is for me
		if( msg.cruzid == id) {	
			msg.num_passwds = ntohl(msg.num_passwds);	
			for(unsigned int i = 0; i < msg.num_passwds; i++) {
				//Make a new thread
				threads.push_back(new std::thread{[&msg, i] {
					
					char crkPass[8];
//					std::cout << i <<": " << msg.passwds[i] <<"\n";
					//Crack passwd
					crack(msg.passwds[i], crkPass);
//					std::cout << "cracked: "<< crkPass << std::endl;
					//Copy cracked str into msg
					strcpy(msg.passwds[i], crkPass);
					}
				});	
			}
			for(std::thread *thread : threads) { 
				thread->join();	
				delete thread;
			}
			threads.clear();
			msg.num_passwds = htonl(msg.num_passwds);

			
			//send(msg)
			int tcpfd = socket(AF_INET, SOCK_STREAM, 0);
			if (tcpfd < 0) error("cracker tcpfd");
			struct hostent *server = gethostbyname(msg.hostname);
			if(server == NULL) error("hostent");
			
			struct sockaddr_in serv_addr;
			bzero((char *) &serv_addr, sizeof(serv_addr));
			serv_addr.sin_family = AF_INET;
			bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
			serv_addr.sin_port = msg.port;
			
			if(connect(tcpfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) error("tcpfd connect");
			int n = write(tcpfd, &msg, sizeof(msg));
			if(n < 0) error("tcpfd write");
			std::cout<< "Sent to: " << msg.hostname <<" at port: " << ntohs(msg.port) << std::endl;
		}
//	}
	close(sockfd);
}
