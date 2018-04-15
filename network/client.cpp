#include "client.h"

int main() {
  Client client = Client(8001, "127.0.0.1");
  std::pair<int, int> *p = client.registerPlayer();
  std::cout << p->first << " - " << p->second << std::endl;
}

Client::Client(int port, std::string addr) {
    this->port = port;
    this->addr = sf::IpAddress(addr);
    this->socket = new sf::TcpSocket();
  }

//Returns <player_id, player_team>
std::pair<int, int> *Client::registerPlayer() {
    if (this->socket->connect(this->addr, this->port, sf::seconds(5)) == sf::Socket::Done) {
      std::cout << "Connected to server!\n";
      sf::Packet packet;
      if (this->socket->receive(packet) == sf::Socket::Done) {
        std::string msg = std::string((const char*)packet.getData(), packet.getDataSize());
        std::istringstream stream = std::istringstream(msg);
        unsigned int player_id, team;
        stream >> player_id >> team;
        return new std::pair<int, int>(player_id, team);
      }
    }
    return NULL;
  }
