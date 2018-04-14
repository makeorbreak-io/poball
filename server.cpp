#include "network/server.h"

int main() {
  Server client = Server(8000, "127.0.0.1");
  client.startListening();
}
