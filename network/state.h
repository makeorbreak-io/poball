#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <string>
#include <SFML/Network.hpp>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <mutex>

class GameState {
private:
  std::unordered_map<int, int*> players;
  int ball[2];
  std::mutex *mutex;

public:
  GameState();

  void updatePlayer(int player_id, unsigned int x, unsigned int y);

  void moveBall(unsigned int x, unsigned int y);

  std::string toString();
};

#endif
