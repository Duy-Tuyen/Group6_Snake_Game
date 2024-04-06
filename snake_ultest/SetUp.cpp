#include "SetUp.h"

vector<Player> players;


void swap(Player& a, Player& b) {
    Player temp;
    temp = a;
    a = b;
    b = temp;
}


void highScore() {
    //Sort function
    for (int i = 0; i < players.size() - 1; i++) {
        for (int j = i + 1; j < players.size(); j++) {
            if (players[i].score < players[j].score) {
                swap(players[i], players[j]);
            }
        }
    }

}

void loadFileScore() {
    ifstream filein("player_info.txt");
    if (!filein.is_open()) {
        cout << "File cannot be found";
    }
    else {
        players.clear();
        std::string line;
        while (std::getline(filein, line)) {
            std::istringstream iss(line);
            std::string playerName, dateAndTime;
            int score;
            // Read player name (can contain spaces)
            std::getline(iss, playerName, ' ');
            // Read score
            iss >> score;
            // Read the rest of the line as date and time
            std::getline(iss >> std::ws, dateAndTime);
            // Create a Player object and add it to the vector
            Player player;
            player.name = playerName;
            player.score = score;
            player.dateAndTime = dateAndTime;
            players.push_back(player);
        }
        filein.close();
    }
}
