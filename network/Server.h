#ifndef SERVER_H
#define SERVER_H

#include <SFML/Network.hpp>
#include "../Logic/game.h"
#include <thread>
#include <list>
#include "../Logic/duck.h"


class Server{
    private:
        Game game;
        sf::TcpListener* listener;
        std::list<sf::TcpSocket*> clients;
        sf::SocketSelector* selector;
        int clientNo;
    public:
        Server();
        void waitClients();
        int sendGameStatus(sf::TcpSocket *client);
        void parseGameStatus(sf::Packet p);
        void serverLoop();
        int sendID(sf::TcpSocket *client);
};

#endif