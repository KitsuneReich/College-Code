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
#include <bits/stdc++.h> //c_str()
#include <crypt.h>

#include <crack.h>

static void error(std::string msg) {
	std::cout << msg << std::endl;
	exit(-1);
}

int main(int argc, char *argv[]) {
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) 
		error("sockfd");
	int ttl = 1; //one-hop multicast option
	if( setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_TTL, (void *) &ttl, sizeof(ttl)) <0) 
		error("setsockopt");

	struct sockaddr_in multicastAddr;
	memset(&multicastAddr, 0, sizeof(multicastAddr) );
	multicastAddr.sin_family = AF_INET;
	multicastAddr.sin_addr.s_addr = get_multicast_address();
	multicastAddr.sin_port = htons(get_multicast_port()); 

	Message msg;
	//Encrypt plain text passwd
	const char *plainPass = argv[2];
	const char *salt = "xx";
	struct crypt_data data;
	data.initialized = 0;
	std::string cryptPass = crypt_r(plainPass, salt, &data);	

	strcpy(msg.cruzid, "nboothro");
    	// Port to return decrypted. unsigned int
	msg.port = htons(get_unicast_port());
	//Set # of passwds
	msg.num_passwds = atoi(argv[1]);
	//Set hostname
	strcpy(msg.hostname, "graculus");
	//Encrypt passwds 
	for (unsigned int i = 0; i < msg.num_passwds; i++) {
		strcpy(msg.passwds[i], cryptPass.c_str() );	
	}
	msg.num_passwds = htonl(msg.num_passwds);	
	

//	while (true) {
		//send(msg);	
		int n = sendto(sockfd, &msg, sizeof(msg), 0, (struct sockaddr *) &multicastAddr, sizeof(multicastAddr));
		if (n < 0)
			error("send");
		sleep(1);
		std::cout << "Sending: " << msg.cruzid << msg.hostname << msg.port << std::endl;
//	}	
	
	int tcpfd = socket(AF_INET, SOCK_STREAM, 0);
	if (tcpfd < 0) error("tcpfd");
	struct sockaddr_in server_addr;
	bzero( (char *) &server_addr, sizeof(server_addr));

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(get_unicast_port());
	
	if( bind(tcpfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) <0) 
		error("bind");
	listen(tcpfd, 5);
	while (true) {
		struct sockaddr_in client_addr;
		socklen_t len = sizeof(client_addr);

		int newsockfd = accept(tcpfd, (struct sockaddr *) &client_addr, &len);
		if (newsockfd < 0) error("accept");
		int n = recv(newsockfd, &msg, sizeof(msg), 0);
		if (n < 0) error("RECEIVE");
		std::cout<< "Received: " << msg.cruzid << std::endl;
		
		close(newsockfd);
	}
	close(sockfd);
}
