#include <string>
#include <SFML/Network.hpp>
#include <iostream>
#include <sstream>
#include <unordered_map>

typedef std::unordered_map<int, sf::TcpSocket*> playerDB;

class Server {
private:
  bool first_player;
  playerDB players;
  bool team_0;
  unsigned int player_id;
  sf::TcpListener *listener;
  sf::SocketSelector *select;
  sf::IpAddress addr;
  unsigned short port;

public:
  Server (int port, std::string addr) {
    this->first_player = true;
    this->team_0 = true;
    this->player_id = 0;
    this->port = port;
    this->select = new sf::SocketSelector();
    this->listener = new sf::TcpListener();
    this->addr = sf::IpAddress(addr);
    this->players = std::unordered_map<int, sf::TcpSocket*>(8);
  }

  // <player_id> <player_team> <x_pos> <y_pos>
  void startListening() {
    sf::TcpSocket client;
    this->listener->listen(this->port, this->addr);

    while (true) {
    if (this->listener->accept(client) == sf::Socket::Done) {
      std::cout << "New conn from " << client.getRemoteAddress() << ":" << client.getRemotePort() << std::endl;

      std::ostringstream reg_msg, new_msg;
      reg_msg << this->player_id << " " << this->team_0;
      this->sendMsg(&client, reg_msg.str().c_str(), reg_msg.str().length());

      new_msg << this->player_id << " "  << this->team_0 << " 123 321";
      this->sendToAll(new_msg.str().c_str(), new_msg.str().length());
      this->updateInfos(client);
    }


    }
  }


  void startServer() {
    while (this->first_player || !this->players.empty()) {
      this->select->wait();
      sf::TcpSocket *socket = this->getReadySocket();
      // update game state 
    }
  }

private:
  sf::TcpSocket *getReadySocket() {
    for (auto it = this->players.begin(); it != this->players.end(); it++) {
      if (this->select->isReady(*it->second)) {
        return it->second;
      }
    }
    return NULL;
  }

  void registerClient(sf::TcpSocket &client) {
    std::cout << "New conn from " << client.getRemoteAddress() << ":" << client.getRemotePort() << std::endl;
    std::ostringstream reg_msg, new_msg;
    reg_msg << this->player_id << " " << this->team_0;
    new_msg << this->player_id << " "  << this->team_0 << " 123 321";
    this->sendMsg(&client, reg_msg.str().c_str(), new_msg.str().length());
    this->sendToAll(new_msg.str().c_str(), new_msg.str().length());
    this->updateInfos(client);
  }

  void updateInfos(sf::TcpSocket &client) {
    this->players[this->player_id] =  &client;
    this->player_id++;
    this->team_0 = !this->team_0;
    this->select->add(client);
  }

  void sendToAll(const char *msg, const unsigned int size) {
    auto it = this->players.begin();
    for (auto it = this->players.begin(); it != this->players.end(); it++) {
      this->sendMsg(it->second, msg, size);
    }
  }

  void sendMsg(sf::TcpSocket *socket, const char *msg, unsigned int size) {
      sf::Packet packet = sf::Packet();
      packet.append(msg, size);
      socket->send(packet);
  }
};

int main() {
  Server client = Server(8001, "127.0.0.1");
  client.startListening();
}
