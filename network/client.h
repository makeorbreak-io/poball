#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <SFML/Network.hpp>
#include <iostream>
#include <sstream>
#include <unordered_map>


class Client {
private:
  sf::TcpSocket *socket;
  sf::IpAddress addr;
  unsigned int port;

public:
  Client(int port, std::string addr);

  std::pair<int, int> *registerPlayer();
};

#endif
