#include "Server.h"

int main(){
    Server s = Server();
    std::cout << "Server created\n";
    s.serverLoop();
    return 0;
}