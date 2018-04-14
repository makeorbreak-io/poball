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

  Client(int port, std::string addr) {
    this->port = port;
    this->addr = sf::IpAddress(addr);
    this->socket = new sf::TcpSocket();
  }

  //Returns <player_id, player_team>
  std::pair<int, int> *registerPlayer() {
    if (this->socket->connect(this->addr, this->port, sf::seconds(5)) == sf::Socket::Done) {
      sf::Packet packet;
      if (this->socket->receive(packet) == sf::Socket::Done) {
        std::string msg = std::string(packet.getData(), packet.getDataSize());
        std::istringstream stream = std::istringstream(msg);
        unsigned int player_id, team;
        stream >> player_id >> team;
        return new std::pair<int, int>(player_id, team);
      }
    }
    return NULL;
  }
};

int main() {
  Client client = Client(8001, "127.0.0.1");
  client.registerPlayer();
}
