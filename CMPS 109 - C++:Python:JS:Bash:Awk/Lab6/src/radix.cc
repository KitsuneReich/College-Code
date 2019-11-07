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

#include "radix.h"

static unsigned int firstDigit(unsigned int n){
	// Remove last digit from number
	// till only one digit is left
	while (n >= 10) 
        n /= 10;
     
	// return the first digit
    	return n;
}

void ParallelRadixSort::msd(std::vector<std::reference_wrapper<std::vector<unsigned int>>> &lists, unsigned int cores) {
    // your implementation goes here :)
    //msd sort base code obtained from: https://opencast-player-1.lt.ucsc.edu:8443/engage/theodul/ui/core.html?id=1a952c7b-5ebd-4215-a514-78fb6adfdb29
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
