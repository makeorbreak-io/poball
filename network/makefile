CC=g++
LIBS=-std=c++11 -lsfml-window -lsfml-network -lsfml-graphics -lsfml-system -lBox2D

ODIR=obj

_OBJS=state.o server.o client.o
OBJS= $(patsubst %,$(ODIR)/%,$(_OBJS))

all: $(ODIR)/state.o server client


$(ODIR)/state.o: state.cpp state.h
	mkdir -p obj
	$(CC) -std=c++11 -c state.cpp -o $@

server: $(ODIR)/state.o server.cpp
	$(CC) $(LIBS) -c -o $(ODIR)/$@.o $@.cpp
	$(CC) $(LIBS) obj/state.o obj/server.o -o $@

client: client.cpp
	$(CC) $(LIBS) -c -o $(ODIR)/client.o $@.cpp
	$(CC) $(LIBS) -o $@ obj/client.o

clean:
	rm -rf obj/
	rm server client
