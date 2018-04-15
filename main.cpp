#include "Logic/game.h"


int main() {
    Game g = Game();
    sf::Thread *listener_thread = new sf::Thread(g.serverListener);
    listener_thread->launch();
    g.update();
    listener_thread->wait();
    return 0;
}
