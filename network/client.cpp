#include "client.h"

Client::Client(int port, std::string addr) {
    this->port = port;
    this->addr = sf::IpAddress(addr);
  }

//Returns <player_id, player_team>
std::pair<int, int> *Client::registerPlayer() {
  std::cout << "Connecting\n";
  if (this->socket->connect(this->addr, this->port, sf::seconds(5)) == sf::Socket::Done) {
    std::cout << "Receibing\n";
    if (this->socket->receive(this->packet) == sf::Socket::Done) {
      sf::UdpSocket udp;
      std::string msg = std::string((const char*)this->packet.getData(), this->packet.getDataSize());
      std::istringstream stream =std::istringstream(msg);
      unsigned int player_id, team;
      std::string addr;
      stream >> player_id >> team >> addr;

      this->setupConnection(addr, this->socket->getLocalPort());
      return new std::pair<int, int>(player_id, team);
    }
  }
  return NULL;
}

void Client::setupConnection(std::string addr, unsigned int port) {
  sf::sleep(sf::seconds(2));
  sf::IpAddress local_addr = sf::IpAddress(addr);
  sf::TcpListener *listener = new sf::TcpListener();
  std::cout << "CENAS\n" << port;
  listener->listen(sf::Socket::AnyPort, local_addr);
  sf::Packet packet;
  std::string data = std::to_string(listener->getLocalPort());
  packet.append(data.c_str(), (std::size_t)data.length());
  this->socket->send(packet);
  this->socket->disconnect();
  std::cout << "CENAS2\n";
  sf::TcpSocket *new_socket = new sf::TcpSocket();
  if (listener->accept(*new_socket) == sf::Socket::Done) {
    std::cout << "Accepted!\n";
    this->socket = new_socket;
  }
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
