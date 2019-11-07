/*
 * Copyright (C) 2018 David C. Harrison. All right reserved.
 *
 * You may not use, distribute, publish, or modify this code without 
 * the express written permission of the copyright holder.
 */
#include <iostream>
#include <vector>
#include "radix.h"

RadixSort::RadixSort(const unsigned int cores) { 

}

// A utility function to get maximum value in vector
unsigned int getMax(std::vector<unsigned int> &vector)
{
    int mx = vector[0];
    for (int i = 0; i < vector.size(); i++) {
        if (vector[i] > mx)
            mx = vector[i];
    }
    return mx;
}

void RadixSort::msd(std::vector<std::reference_wrapper<std::vector<unsigned int>>> &lists) { 
    // your implementation goes here :)
    std::vector<unsigned int> &intVector = lists.front();
    
    for (unsigned int i = 0; i < lists.size(); i++) {
        unsigned int value = getMax(intVector);
        std::cout << value << std::endl;
    }
}
