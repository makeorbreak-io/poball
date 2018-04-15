#ifndef SERVER_H
#define SERVER_H

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


class Server {
  const double PERIOD = 0.0033;
  GameState state;
  bool first_player;
  bool team_0 = true;
  unsigned int port, player_id;
  sf::SocketSelector *select;
  sf::TcpListener *listener;
  sf::IpAddress addr;
  std::unordered_map<int, sf::TcpSocket *> players;
  std::chrono::time_point<std::chrono::_V2::system_clock, std::chrono::duration<long int, std::ratio<1, 1000000000> > > prev_time;


public:
  Server(int port, std::string addr);
  void startListening();
  void startServer();

private:
  void sendState();
  double timeToSend();
  sf::TcpSocket *getReadySocket();
  void registerClient(sf::TcpSocket &client);
  void updateInfos(sf::TcpSocket &client);
  void sendToAll(const char *msg, unsigned int size);
  void sendMsg(sf::TcpSocket *socket, const char *msg, unsigned int size);
};

#endif
