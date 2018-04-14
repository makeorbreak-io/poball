#include "state.h"

GameState::GameState() {
  this->mutex = new std::mutex();
  this->players = std::unordered_map<int, int*>();
}

void GameState::updatePlayer(int player_id, unsigned int x, unsigned int y) {
  int coordinates[100];
  coordinates[0] = x;   coordinates[1] = y;
  this->mutex->lock();
  this->players[player_id] = coordinates;
  this->mutex->unlock();
}

void GameState::moveBall(unsigned int x, unsigned int y) {
  this->mutex->lock();
  this->ball[0] = x;  this->ball[1] = y;
  this->mutex->unlock();
}

// Returns the game state in the following form, the first line is theball coordinates
// STATE \n
// <ball_x_coordinate> <ball_y_coordinate> \n
// <player1> <x> <y> \n
// <player2> <x> <y> \n
std::string GameState::toString() {
  std::ostringstream stream;
  stream << "STATE\n";
  this->mutex->lock();
  stream << ball[0] << " " << ball[1] << "\n";
  for (auto it = this->players.begin(); it != this->players.end();it++) {
    stream << it->first << " " << it->second[0] << " " << it->second[1]<< "\n";
  }
  this->mutex->unlock();
  return stream.str();
}
