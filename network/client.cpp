#include "client.h"

Client::Client(int port, std::string addr) {
    this->port = port;
    this->addr = sf::IpAddress(addr);
    this->socket = new sf::TcpSocket();
  }

//Returns <player_id, player_team>
std::pair<int, int> *Client::registerPlayer() {
  std::cout << "Connecting\n";
  if (this->socket->connect(this->addr, this->port, sf::seconds(5)) == sf::Socket::Done) {
    std::cout << "Receibing\n";
    if (this->socket->receive(this->packet) == sf::Socket::Done) {
      std::cout << "Received\n";
      std::string msg = std::string((const char*)this->packet.getData(), this->packet.getDataSize());
      std::istringstream stream =std::istringstream(msg);
      unsigned int player_id, team;
      stream >> player_id >> team;
      this->packet.clear();
      return new std::pair<int, int>(player_id, team);
    }
  }
  return NULL;
}

std::istringstream Client::getServerMsg() {
  char * data;
  auto status = this->socket->receive(this->packet);

  data = (char *)this->packet.getData();
  switch (status) {
    case sf::Socket::Done:
    {
      std::cout << "Done\n";
      std::string msg = std::string(data, this->packet.getDataSize());
      this->packet.clear();
      return std::istringstream(msg);
    }
    break;
    case sf::Socket::NotReady: std::cout << "Not Ready!!!\n"; break;
    case sf::Socket::Partial: std::cout << "Partial!!!\n"; break;
    case sf::Socket::Disconnected:  std::cout << "Disconnected!!!\n"; break;
  }
}
