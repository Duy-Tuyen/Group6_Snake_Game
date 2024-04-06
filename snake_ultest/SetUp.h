#pragma once
#include "Graphics.h"
#include "fstream"
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

struct Player {
	string name, dateAndTime;
	int score;

	Player() {
		name = "";
		dateAndTime = "";
		score = 0;
	}
};

extern vector<Player> players;

void highScore();
void swap(Player& a, Player& b);
void loadFileScore();
