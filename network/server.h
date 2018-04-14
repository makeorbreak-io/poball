#ifndef SERVER_H
#define SERVER_H

#include "state.h"
#include <string>
#include <SFML/Network.hpp>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <chrono>

typedef std::unordered_map<int, sf::TcpSocket*> playerDB;

class Server {
  GameState state;
  const double PERIOD = 0.0033;
  bool first_player;
  playerDB players;
  bool team_0;
  unsigned int player_id;
  sf::TcpListener *listener;
  sf::SocketSelector *select;
  sf::IpAddress addr;
  unsigned short port;
  std::chrono::time_point<std::chrono::_V2::system_clock, std::chrono::duration<long, std::ratio<1, 1000000000> > > prev_time;

public:
  Server (int port, std::string addr);
  void startListening();
  void startServer();

private:
  void sendState();

  double timeToSend();

  sf::TcpSocket *getReadySocket();

  void registerClient(sf::TcpSocket &client);

  void updateInfos(sf::TcpSocket &client);

  void sendToAll(const char *msg, const unsigned int size);

  void sendMsg(sf::TcpSocket *socket, const char *msg, unsigned int size);
};

#endif
