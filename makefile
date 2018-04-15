CC=g++
LIBS=-std=c++11 -lsfml-window -lsfml-network -lsfml-graphics -lsfml-system -lBox2D -g
SUBDIRS=Logic network

LOGIC_OBJS=$(wildcard Logic/obj/*.o)
NET_OBJS=$(wildcard network/obj/*.o)

poball: server logic
	$(CC) $(LIBS) -o poball main.cpp $(LOGIC_OBJS) network/obj/client.o

server: $(SUBDIRS)
	$(MAKE) -C network
	$(CC) $(LIBS) -o server network/server.cpp


logic: $(SUBDIRS)
		$(MAKE) -C Logic

clean:
	$(MAKE) -C Logic $(MAKECMDGOALS)
	$(MAKE) -C network $(MAKECMDGOALS)
	rm server
	rm poball

.PHONY: all $(SUBDIRS)
