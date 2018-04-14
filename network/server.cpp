#include "server.h"


Server::Server (int port, std::string addr) {
    this->first_player = true;
    this->team_0 = true;
    this->player_id = 0;
    this->port = port;
    this->select = new sf::SocketSelector();
    this->listener = new sf::TcpListener();
    this->addr = sf::IpAddress(addr);
    this->players = std::unordered_map<int, sf::TcpSocket*>(8);
    this->state = GameState();
  }

// <player_id> <player_team> <x_pos> <y_pos>
void Server::startListening() {
    sf::TcpSocket client;
    this->listener->listen(this->port, this->addr);

    while (true) {
    if (this->listener->accept(client) == sf::Socket::Done) {
      std::cout << "New conn from " << client.getRemoteAddress() << ":" << client.getRemotePort() << std::endl;

      std::ostringstream reg_msg, new_msg;
      reg_msg << this->player_id << " " << this->team_0 << "\n";
      this->sendMsg(&client, reg_msg.str().c_str(), reg_msg.str().length());

      new_msg << "NEW_PLAYER\n" << this->player_id << " "  << this->team_0 << " 123  321\n";
      this->updateInfos(client);
      this->sendToAll(new_msg.str().c_str(), new_msg.str().length());
    }


    }
  }


// Receives <message_type> <player_id> <player_x> <player_y> <ball_x?><ball_y?>
void Server::startServer() {
  sf::Packet packet;
  while (this->first_player || !this->players.empty()) {
      this->select->wait();
      sf::TcpSocket *socket = this->getReadySocket();
      socket->receive(packet);
      std::istringstream stream = std::istringstream(std::string((const char*)packet.getData(), packet.getDataSize()));

      this->sendState();
    }
}

void Server::sendState() {
  if (this->timeToSend()) {
    std::string state = this->state.toString();
    this->sendToAll(state.c_str(), state.length());
  }
}

double Server::timeToSend() {
  auto end = std::chrono::high_resolution_clock::now();
  auto diff = end - this->prev_time;
  if (diff.count() >= this->PERIOD) {
    this->prev_time = end;
    return true;
  }
  return false;
}

sf::TcpSocket *Server::getReadySocket() {
  for (auto it = this->players.begin(); it != this->players.end(); it++) {
    if (this->select->isReady(*it->second)) {
      return it->second;
    }
  }
  return NULL;
}

void Server::registerClient(sf::TcpSocket &client) {
  std::cout << "New conn from " << client.getRemoteAddress() << ":" << client.getRemotePort() << std::endl;
  std::ostringstream reg_msg, new_msg;
  reg_msg << this->player_id << " " << this->team_0;
  new_msg << this->player_id << " "  << this->team_0 << " 500 500";
  this->sendMsg(&client, reg_msg.str().c_str(), new_msg.str().length());
  this->sendToAll(new_msg.str().c_str(), new_msg.str().length());
  this->updateInfos(client);
}

void Server::updateInfos(sf::TcpSocket &client) {
  if (this->player_id == 0) { //First player will be host
    this->state.moveBall(150, 150);
  }
  this->state.updatePlayer(player_id, 25, 25);
  this->players[this->player_id] =  &client;
  this->player_id++;
  this->team_0 = !this->team_0;
  this->select->add(client);
}

void Server::sendToAll(const char *msg, const unsigned int size) {
  auto it = this->players.begin();
  for (auto it = this->players.begin(); it != this->players.end(); it++) {
    std::cout << "IS NULL? " << (it->second == NULL) << "\n";
    this->sendMsg(it->second, msg, size);
  }
}

void Server::sendMsg(sf::TcpSocket *socket, const char *msg, unsigned int size) {
    sf::Packet packet = sf::Packet();
    std::cout << "Sending: '" << msg << "'\n";
    packet.append(msg, size);
    auto status = socket->send(packet);
    if (status == sf::Socket::Done) {
      std::cout << "Freaking done!\n";
    }
    else {
      std::cout << "FUUUUCKKKKKK\n";
    }
}
