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
	bucket[i].clear();
	}
     }
}

RadixServer::RadixServer(const int port, const unsigned int cores) {
    // your server implementation goes here :)
    
    int sockfd = socket(AF_INET, SOCK_STREAM,0);
    if(sockfd < 0)
	exit(-1);
    struct sockaddr_in server_addr;
    bzero((char *) &server_addr, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if(bind(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) 
	exit(-1);
    listen(sockfd, 5);

    std::vector<unsigned int> list;		
    unsigned int number;

    struct sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr);

    int newsockfd = accept(sockfd, (struct sockaddr *) &client_addr, &len);
    if (newsockfd < 0)
	exit(-1);

    for(;;) {
	int n = recv(newsockfd, &number, sizeof(number), 0);
	    if(n < 0)
		exit(-1);
	    else if(n == 0) {
		break;
	    } 
	    else if(number == 0) {
	 	//handle disconnect

    		//Reference vector for passing to msd();
    		std::vector<std::reference_wrapper<std::vector<unsigned int>>> lists;
    		lists.push_back(list);
   		 ParallelRadixSort sorter;
   		 sorter.msd(lists, cores); 

   		 for (unsigned int &number : list) {
    			unsigned int data = htonl(number);
    			int n = write(newsockfd, &data, sizeof(data));
    			if(n < 0)
				exit(-1);
//    			std::cout << "Server Sent: " << number << std::endl;
    		}
    		unsigned int end = 0;
    		int n = write(newsockfd, &end, sizeof(end));
    		if(n < 0)
			exit(-1);
//		std::cout << "Server Sent: " << end  << std::endl;
		list.clear();
	    }
	    else {
		unsigned int data = ntohl(number);
//		std::cout<< "Server Received: " << data << std::endl;
		list.push_back(data);
	    }
    }

    close(newsockfd);
    close(sockfd);
}

void RadixClient::msd(const char *hostname, const int port, std::vector<std::reference_wrapper<std::vector<unsigned int>>> &lists) { 
    // your client implementation goes here :) 
    
    //Create Socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
	exit(-1);

    //Change hostname from string into number
    struct hostent *server = gethostbyname(hostname);
    if (server == NULL) 
	exit(-1);
    struct sockaddr_in serv_addr;
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
 
    serv_addr.sin_port = htons(port);

    if(connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr) ) < 0 ) 
	exit(-1);

    for (std::vector<unsigned int> &list : lists) {		
	for (unsigned int &number : list) {
    		unsigned int data = htonl(number);
		int n = write(sockfd, &data, sizeof(data));
		if (n<0)
			exit(-1);
//		std::cout<< "Send: " <<number << std::endl;
    	}
	//Mark the end of the list with a 0 for server
	int end = 0;
	int n = write(sockfd, &end, sizeof(end));
	if(n<0)
		exit(-1);
	list.clear();
	//Read Back from Server
	unsigned int result = 17;		
     	while(result != 0) {
		n = read(sockfd,&result, sizeof(result));
		if(n<0)
			exit(-1);
		unsigned int data = ntohl(result);
//		std::cout<< "Received: "<< data << std::endl;
		if(data != 0) {
			list.push_back(data);	
   		}
	}
    }
    close(sockfd);
}
