#include "Client.h"
#include <iostream>
#include <stdlib.h>
#include <sstream>

Client::Client()
{
    this->socket = new sf::TcpSocket();
    this->game = new Game();
    std::cout << "Client constructed\n";
}

int Client::connectServer(int port, std::string ip)
{
    sf::IpAddress ipAddress = sf::IpAddress(ip);
    std::cout << "Trying to connect to server\n";
    sf::Socket::Status status = this->socket->connect(ipAddress, port, sf::seconds(5));
    int ret;
    switch (status)
    {
    case sf::Socket::Status::Disconnected:
        std::cout << "Disconected\n";
        ret = -1;
        break;
    case sf::Socket::Status::Done:
        std::cout << "Done\n";
        ret = 0;
        break;
    case sf::Socket::Status::Error:
        std::cout << "Error\n";
        ret = -1;
        break;
    case sf::Socket::Status::NotReady:
        std::cout << "Not ready\n";
        ret = -1;
        break;
    case sf::Socket::Status::Partial:
        std::cout << "Partial\n";
        ret = -1;
        break;
    }
    return ret;
}

int Client::getGameState()
{
    std::cout << "Receiving game state\n";
    sf::Packet packet;
    sf::Socket::Status status = this->socket->receive(packet);
    int ret;
    switch (status)
    {
    case sf::Socket::Status::Disconnected:
        std::cout << "Disconected\n";
        ret = -1;
        break;
    case sf::Socket::Status::Done:
    {
        std::cout << "Done\n";
        const void *g = packet.getData();
        this->parseReceivedGameState(g, packet.getDataSize());
        ret = 0;
        break;
    }
    case sf::Socket::Status::Error:
        std::cout << "Error\n";
        ret = -1;
        break;
    case sf::Socket::Status::NotReady:
        std::cout << "Not ready\n";
        ret = -1;
        break;
    case sf::Socket::Status::Partial:
        std::cout << "Partial\n";
        ret = -1;
        break;
    }

    return ret;
}

void Client::parseReceivedGameState(const void *g, size_t datasize)
{
    std::string res(static_cast<const char *>(g), datasize);
    std::cout << "Parsing received game state..." << res << std::endl;
    std::stringstream test("this_is_a_test_string");
    std::string segment;
    std::vector<std::string> seglist;
    while (std::getline(test, segment, ' '))
    {
        seglist.push_back(segment);
    }
    float xF = std::stof(seglist.at(0));
    float yF = std::stof(seglist.at(1));
    this->game->getBall()->getBody()->SetTransform(b2Vec2(xF, yF), 0);
}

void Client::gameLoop()
{
    std::thread gameLogicUpdate(&Game::update, this->game);
    std::thread gameClientUpdate(&Client::sendReceiveLoop, this);

    gameLogicUpdate.join();
    gameClientUpdate.join();
}

int Client::sendReceiveLoop()
{
    std::cout << "Send/Receive Loop...\n";
    int r;
    while (true)
    {
        r = this->sendDuck();
        if (r == -1)
        {
            std::cout << "Error sending the duck!\n";
            return r;
        }
        r = this->getGameState();
        if (r == -1)
        {
            std::cout << "Error receiving game state!\n";
            return r;
        }
    }
}

int Client::sendDuck()
{
    sf::Packet packet;
    packet.append(this->game->getDuck(), sizeof(this->game->getDuck()));
    sf::Socket::Status status = this->socket->send(packet);
    std::cout << "Sent duck...\n";
    int r;
    switch (status)
    {
    case sf::Socket::Status::Disconnected:
        std::cout << "Disconected\n";
        r = -1;
        break;
    case sf::Socket::Status::Done:
        std::cout << "Done\n";
        r = 0;
        break;
    case sf::Socket::Status::Error:
        std::cout << "Error\n";
        r = -1;
        break;
    case sf::Socket::Status::NotReady:
        std::cout << "Not ready\n";
        r = -1;
        break;
    case sf::Socket::Status::Partial:
        std::cout << "Partial\n";
        r = -1;
        break;
    }
    return r;
}

int Client::learnID()
{
    sf::Packet packet;
    sf::Socket::Status status = this->socket->receive(packet);
    int ret;
    switch (status)
    {
    case sf::Socket::Status::Disconnected:
        std::cout << "Disconected\n";
        ret = -1;
        break;
    case sf::Socket::Status::Done:
    {
        std::cout << "Done\n";
        const char *g = (const char *)packet.getData();
        this->game->getDuck()->id = atoi(g);
        std::cout << "Received id ... " << this->game->getDuck()->id << std::endl;
        ret = 0;
        break;
    }
    case sf::Socket::Status::Error:
        std::cout << "Error\n";
        ret = -1;
        break;
    case sf::Socket::Status::NotReady:
        std::cout << "Not ready\n";
        ret = -1;
        break;
    case sf::Socket::Status::Partial:
        std::cout << "Partial\n";
        ret = -1;
        break;
    }

    return ret;
}
