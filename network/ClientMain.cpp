#include "Client.h"

int main(){
    Client c = Client();
    int r = c.connectServer(8000,"127.0.0.1");
    if(r != 0){
        std::cout<< "Error connecting to server!\n";
        return -1;
    }
    r = c.learnID();
    if(r == -1){
        std::cout << "Could not learn id...\n";
        return -1;
    }
    c.gameLoop();
    return 0;
}