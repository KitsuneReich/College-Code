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
};

template <class T>

class Leaderboard {
private:
	vector<T> high_scores;
	int index;
public:
	Leaderboard() { index = 0; }
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
	cout << "\t\tHIGH SCORES\n\n"
		<< "RANK\tSCORE\tNAME\n\n";
	for (int it = 0; it < index; it++) {
		if (it == 0) { cout << "1st\t"; }
		else if (it == 1) { cout << "2nd\t"; }
		else if (it == 2) { cout << "3rd\t"; }
		else { cout << it + 1 << "th\t"; }

		cout << high_scores.at(it).player << "\t" << high_scores.at(it).score << endl;
	}
}

template <typename T> void Leaderboard<T>::store() {
	ofstream saveScore;
	int size = high_scores.size();
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
		cout << "ERROR\n";
		return;
	}
}
template <typename T> void Leaderboard<T>::sort() {
	int temp;
	int flag = 1;
	for (int i = 0; (i <= high_scores.size() && flag); i++) {
		flag = 0;
			for (int n = 0; n < (high_scores.size() - 1); n++) {
				if (high_scores.at(n + 1).score > high_scores.at(n).score) {
					game temp;
						temp.player = high_scores.at(n).player;
						temp.score = high_scores.at(n).score;

						high_scores.at(n) = high_scores.at(n + 1);
						high_scores.at(n + 1) = temp;

						flag = 1;
				}
			}
	}
}