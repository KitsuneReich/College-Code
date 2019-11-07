//---------------------------------------------------------------------------------
// CIT 66 Fall 2015 | Fresno City College
//
// Boothroyd, Nichole
//
// Language:     C++
//
// Description:  A class Leaderboard which stores high scores and player initials
//               into structs called game. These high scores are saved to a txt
//               file which can be loaded on the next run.
//
// Usage:        #include "score.h"
//
//---------------------------------------------------------------------------------
#pragma once
#include <iostream>
#include <cstdlib>
#include <string>
#include <array>
#include <fstream>
#include <vector>
using namespace std;

struct game {
	string player;
	int score;
    
    bool operator>(const game& a) {
        if (score >= a.score)
            return true;
        else
            return false;
    }
    void operator=(const game &a) {
        score = a.score;
        player = a.player;
     }
};

template <class T> 

class Leaderboard {
private:
	vector<T> high_scores;
	int index;
public:
	Leaderboard() {index = 0;}
	void addScore(string, int);
	void print();
	void store();
	void load();
    void sort();
};

template <typename T> void Leaderboard<T>::addScore(string name, int score) {
        game temp;
        temp.player = name;
        temp.score = score;
        high_scores.push_back(temp);
        index++;
}

template <typename T> void Leaderboard<T>::print() {
	int size = high_scores.size();
    if(size > 0) {
        cout << "\t\tHIGH SCORES\n\n"
    		<< "RANK\tSCORE\tNAME\n\n";
        for (int it = 0; it < size; it++) {
    		if (it == 0) { cout << "1st\t"; }
    		else if (it == 1) { cout << "2nd\t"; }
    		else if (it == 2) { cout << "3rd\t"; }
    		else { cout << it + 1 << "th\t"; }
    	
    		cout << high_scores.at(it).player << "\t" << high_scores.at(it).score << endl;
    	}
    }
    else {
        cout << "No high scores" << endl;
    }
}

template <typename T> void Leaderboard<T>::store() {
	ofstream saveScore;
    int size = high_scores.size();
    
    if (size > 10) {
        size = 10;    
    }
    
	saveScore.open("saveS.txt", ios::out);
	if (saveScore.is_open()) {
		for (int i = 0; i < size; i++) {
			int num = high_scores.at(i).score;
			string name = high_scores.at(i).player;
			
			saveScore << name << endl;
			saveScore << num << endl;
		}
	}
	saveScore.close();
}

template <typename T> void Leaderboard<T>::load() {
	
	string name, sscore;
	int score;
	ifstream loadS;
	ifstream loadN;

	loadS.open("saveS.txt", ios::in);

	if (loadS.is_open()) {
		getline(loadS, name);
		getline(loadS, sscore);

		while (!loadS.eof()) {
			score = stoi(sscore, nullptr);

			this->addScore(name, score);

			getline(loadS, name);
			getline(loadS, sscore);
		}
		loadS.close();
	}

	else {
	cout <<"ERROR\n";
		return;
	}
}

template <typename T> void Leaderboard<T>::sort() {    
    for(int i = 0; i < high_scores.size(); i++) {
        for(int j = i+1; j < high_scores.size(); j++) {
            if(high_scores[j] > high_scores[i]) {
                game temp;
                temp = high_scores[i];
                
                high_scores[i] = high_scores[j];
                high_scores[j] = temp;
            }
        }
    }
}
