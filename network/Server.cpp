#include "Server.h"
#include <iostream>
#include <string>

Server::Server()
{
    this->game = Game();
    this->selector = new sf::SocketSelector();
    this->listener = new sf::TcpListener();
    this->listener->listen(8000, sf::IpAddress("127.0.0.1"));
    this->selector->add(*this->listener);
    this->clientNo = 0;
}

void Server::waitClients()
{
    std::cout << "Endless loop that waits for new connections\n";
    while (true)
    {
        // Make the selector wait for data on any socket
        if (this->selector->wait())
        {
            // Test the listener
            if (this->selector->isReady(*this->listener))
            {
                std::cout << "The listener is ready: there is a pending connection\n";
                sf::TcpSocket *client = new sf::TcpSocket;
                if (this->listener->accept(*client) == sf::Socket::Done)
                {
                    std::cout << "Add the new client to the clients list and selector\n";
                    clients.push_back(client);
                    // Add the new client to the selector so that we will
                    // be notified when he sends something
                    this->selector->add(*client);
                    this->sendID(client);
                }
                else
                {
                    std::cout << "Error, we won't get a new connection, delete the socket\n";
                    delete client;
                }
            }
            else
            {
                //std::cout << "The listener socket is not ready, test all other sockets (the clients)\n";
                for (std::list<sf::TcpSocket *>::iterator it = clients.begin(); it != clients.end(); ++it)
                {
                    sf::TcpSocket &client = **it;
                    if (this->selector->isReady(client))
                    {
                        //std::cout << "The client has sent some data, we can receive it\n";
                        sf::Packet packet;
                        if (client.receive(packet) == sf::Socket::Done)
                        {
                            this->parseGameStatus(packet);
                            this->sendGameStatus(&client);
                        }
                    }
                }
            }
        }
    }
}

int Server::sendGameStatus(sf::TcpSocket *client)
{
    sf::Packet packet;
    std::string x = std::to_string(this->game.getBall()->getBody()->GetPosition().x);
    std::string y = std::to_string(this->game.getBall()->getBody()->GetPosition().y);
    std::string res = x + " " + y;
    std::cout << "Sending..." << res << std::endl;
    packet.append(&res, sizeof(res));
    sf::Socket::Status status = client->send(packet);
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

void Server::parseGameStatus(sf::Packet p)
{
}

void Server::serverLoop()
{
    std::cout << "Starting server loop...\n";
    std::thread gl(&Game::update, this->game);
    std::cout << "Waiting for clients...\n";
    std::thread wait(&Server::waitClients, this);

    wait.join();
    gl.join();
}

int Server::sendID(sf::TcpSocket *client)
{
    std::cout << "Sending id ... " << this->clientNo << std::endl;
    sf::Packet packet;
    packet.append(&this->clientNo, sizeof(this->clientNo));
    sf::Socket::Status status = client->send(packet);
    this->clientNo++;
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