CC=g++
LIBS=-std=c++11 -lsfml-window -lsfml-network -lsfml-graphics -lsfml-system -lBox2D
SUBDIRS=Logic network

LOGIC_OBJS=$(wildcard Logic/obj/*.o)
NET_OBJS=$(wildcard network/obj/*.o)

poball: server logic
	$(CC) $(LIBS) -o poball main.cpp $(LOGIC_OBJS) $(NET_OBJS)

server: $(SUBDIRS)
	$(MAKE) -C network
	$(CC) $(LIBS) -o server server.cpp network/obj/server.o network/obj/state.o


logic: $(SUBDIRS)
		$(MAKE) -C Logic

clean:
	$(MAKE) -C Logic $(MAKECMDGOALS)
	$(MAKE) -C network $(MAKECMDGOALS)
	rm poball
	rm server

.PHONY: all $(SUBDIRS)
