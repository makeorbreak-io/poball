#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <SFML/Network.hpp>
#include <iostream>
#include <sstream>
#include <unordered_map>


class Client {
private:
  sf::TcpSocket *socket = new sf::TcpSocket();
  sf::Packet packet;
  sf::IpAddress addr;
  unsigned int port;

public:
  Client(int port, std::string addr);

  std::pair<int, int> *registerPlayer();

  std::istringstream getServerMsg();

private:
  void setupConnection(std::string addr, unsigned int port);
};

#endif
