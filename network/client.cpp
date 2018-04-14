#include "client.h"

Client::Client(int port, std::string addr) {
    this->port = port;
    this->addr = sf::IpAddress(addr);
    this->socket = new sf::TcpSocket();
  }

//Returns <player_id, player_team>
std::pair<int, int> *Client::registerPlayer() {
  if (this->socket->connect(this->addr, this->port,sf::seconds(5)) == sf::Socket::Done) {
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
  this->packet.clear();
  return NULL;
}

std::istringstream Client::getServerMsg() {
  auto status = this->socket->receive(this->packet);
  const char *data = (const char*)this->packet.getData();
  std::cout << "EOPacket = " << this->packet.endOfPacket() << "\n";

  if (data != NULL) {
    std::cout << "Done\n";
    std::cout << "Size = " << this->packet.getDataSize() << "\n";
    std::string msg = std::string((const char*)this->packet.getData(), this->packet.getDataSize());
    this->packet.clear();
    return std::istringstream(msg);
  }
  else {
    std::cout << "Not done!!!\n";
  }


}
