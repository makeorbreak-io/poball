#ifndef CLIENT_H
#define CLIENT_H

#include <SFML/Network.hpp>
#include <thread>
#include "../Logic/game.h"


class Client{
    private:
        Game  * game;
        sf::TcpSocket* socket;
    public:
        Client();
        int connectServer(int port , std::string ipAddress);
        int learnID();
        int getGameState();
        void gameLoop();
        void parseReceivedGameState(const void * g,size_t dataSize);
        int sendReceiveLoop();
        int sendDuck();
};


#endif