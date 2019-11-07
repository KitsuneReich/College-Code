/*
 * Copyright (C) 2018 David C. Harrison. All right reserved.
 *
 * You may not use, distribute, publish, or modify this code without 
 * the express written permission of the copyright holder.
 */

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
#include <netdb.h>

#include "radix.h"

static unsigned int firstDigit(unsigned int n){
	// Remove last digit from number
	// till only one digit is left
	while (n >= 10) 
        n /= 10;
     
	// return the first digit
    	return n;
}

static void clearMsg(Message &msg) {
	msg.num_values = 0;
	msg.sequence = 0;
	msg.flag = htonl(NONE);	
}
static void ntohlMsg(Message &msg) {
	msg.num_values = ntohl(msg.num_values);
        msg.sequence = ntohl(msg.sequence);
        msg.flag = ntohl(msg.flag);
}

void ParallelRadixSort::msd(std::vector<std::reference_wrapper<std::vector<unsigned int>>> &lists, const unsigned int cores) { 

    // your implementation goes here :)
    std::vector<std::vector<unsigned int>> bucket(10);
    std::vector<std::thread*> threads;
    //    unsigned int numberOfThreads;
    //For each list in the List of Lists...
    for (std::vector<unsigned int> &list : lists) {	
	//For each number in the list
	for (unsigned int &number : list) {
		//Get first digit of the number
		unsigned int n = firstDigit(number);
		//Place number into appropriate digit bucket
		bucket[n].push_back(number);	
	}
	list.clear();	
	for (unsigned int i = 1; i < 10; i++) {
	//Sort the Buckets
	std::sort(bucket[i].begin(), bucket[i].end(), [](const unsigned int& a, const unsigned int& b) {
			return std::to_string(a).compare(std::to_string(b)) < 0;
			}
	);
		for (std::vector<unsigned int>::iterator it = bucket[i].begin() ; it != bucket[i].end(); ++it) {
			list.push_back(*it);
		}
	}
    }
}

/*
 * Start a UDP listener on PORT and accept lists of unsiged integers from
 * clients to be MSD RAdix sorted using no more that CORES cpu cores. After
 * sorting the lists are to be retiurned to the client.
 */
void RadixServer::start(const int port, const unsigned int cores) {
    std::vector<std::reference_wrapper<std::vector<unsigned int>>> lists;
    std::vector<unsigned int> list;
    Message msg; 
    
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
	exit(-1);
    
    //Create Socket
    struct sockaddr_in server_addr;
    bzero((char*) &server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    //Bind to port
    if(bind(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
	exit(-1);
    
    struct sockaddr_in remote_addr;
    socklen_t length = sizeof(remote_addr);

    //Now listen for any requests

    while (true) {	
	if(recvfrom(sockfd, &msg, sizeof(msg), 0, (struct sockaddr *) &remote_addr, &length ) < 0 ) 
        	exit(-1);
	//Recieved a msg with num_value with number of elements
	ntohlMsg(msg);

	//For each number in the datagram
	for (unsigned int i = 0; i < msg.num_values; i++) {
		//Convert the number's byte order
		unsigned int data = ntohl(msg.values[i]);
		//and push onto the list
		list.push_back(data);
	}
	if (msg.flag == LAST) {
//		std::cout<< "List size: " << list.size()  << std::endl;
    	 	//sort
		lists.push_back(list);
   		ParallelRadixSort sorter;
   		sorter.msd(lists, cores); 
		
		//Clear Values
		clearMsg(msg);
		
		for (unsigned int &number : list) {	
    			msg.values[msg.num_values++] =  number;
			if (msg.num_values == 128) {
				//send(msg)	
				msg.sequence = htonl(msg.sequence);
				msg.num_values = htonl(msg.num_values);	
				for (unsigned int &number : msg.values) {
					number = htonl(number);	
				}
			if(sendto(sockfd, &msg, sizeof(msg), 0, (struct sockaddr *) &remote_addr, length ) < 0 ) 
				exit(-1);
			//Reset values
			msg.sequence = ntohl(msg.sequence);
			msg.sequence++;
			msg.num_values = 0;
			}
		}
		msg.sequence = htonl(msg.sequence);
		msg.num_values = htonl(msg.num_values);
		msg.flag = htonl(LAST);
		for (unsigned int &number : msg.values) {
			number = htonl(number);	
		}
		
		if(sendto(sockfd, &msg, sizeof(msg), 0, (struct sockaddr *) &remote_addr, length ) < 0 ) 
			exit(-1);
//		std::cout<< "Sending message #: " << msg.sequence << std::endl;

		//Clear the list to recv sorted list from server
		list.clear();
		lists.clear();
	} 
    }
	close(sockfd);	
}

/*
 * Shutdown the server. Typically this will involve closing the server socket.
 */
void RadixServer::stop() {
	//Kon Kon!
}

/*
 * Send the contents of the lists contained with LISTS to the server on HIOSTNAME
 * listening on PORT in datagrams containing batches of unsigned integers. These
 * will be returned to you MSD Radix sorted and should be retied to the caller
 * via LISTS.
 */
void RadixClient::msd(const char *hostname, const int port, std::vector<std::reference_wrapper<std::vector<unsigned int>>> &lists) { 

    //Create Socket
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) 
	exit(-1);

    //Change hostname from string into number
    struct hostent *server = gethostbyname(hostname);
    if (server == NULL) 
	exit(-1);
    struct sockaddr_in remote_addr;
    bzero((char *) &remote_addr, sizeof(remote_addr));
    remote_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&remote_addr.sin_addr.s_addr, server->h_length);
 
    remote_addr.sin_port = htons(port);
    socklen_t length = sizeof(remote_addr);		

    //create a variable to hold the message { VALUE, SEQUENCE, FLAG }
    Message msg;

    for (std::vector<unsigned int> &list : lists) {	
	clearMsg(msg);
	
	for (unsigned int &number : list) {	
    		msg.values[msg.num_values++] =  number;
		if (msg.num_values == 128) {
			msg.sequence = htonl(msg.sequence);
			msg.num_values = htonl(msg.num_values);
			for (unsigned int &number : msg.values) {
				number = htonl(number);	
			}
		
			if(sendto(sockfd, &msg, sizeof(msg), 0, (struct sockaddr *) &remote_addr, length ) < 0 ) 
		exit(-1);
			
			//Clear values
//			std::cout<< msg.sequence << std::endl;
			msg.sequence = ntohl(msg.sequence);
			msg.sequence++;
//			std::cout<< msg.sequence << std::endl;
			msg.num_values = 0;
		}
	}	
	msg.sequence = htonl(msg.sequence);
	msg.num_values = htonl(msg.num_values);
	msg.flag = htonl(LAST);
	for (unsigned int &number : msg.values) {
		number = htonl(number);	
	}
		
	if(sendto(sockfd, &msg, sizeof(msg), 0, (struct sockaddr *) &remote_addr, length ) < 0 ) 
		exit(-1);
//	std::cout<< "Sending message #: " << msg.sequence << std::endl;

	//Clear the list to recv sorted list from server
	list.clear();
	//Read Back from Server

	unsigned int recvPackets = -1;	
     	do {
		if(recvfrom(sockfd, &msg, sizeof(msg), 0, (struct sockaddr *) &remote_addr, &length ) < 0 ) 
        		exit(-1);
		//Convert to host order
		recvPackets++;
		ntohlMsg(msg);

		std::cout<< msg.sequence << std::endl;
		//if RESEND:
		if(msg.flag == RESEND){
			std::cout<<"Resend Request" << std::endl;
		}
		if( msg.sequence > recvPackets) {
			std::cout<< "missing packet" << std::endl;
			
		}
		for (unsigned int i = 0; i < msg.num_values; i++) {
			unsigned int data = ntohl(msg.values[i]);
//			std::cout<< "Received: "<< data << std::endl;
			list.push_back(data);	
		}
	
    	}while (msg.flag == NONE);
    }
    //close connection after all lists have been processed 
    close(sockfd);
}
