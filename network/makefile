CC=g++
LIBS=-std=c++11 -lsfml-window -lsfml-network -lsfml-graphics -lsfml-system -lBox2D

ODIR=obj

_OBJS=server.o client.o
OBJS= $(patsubst %,$(ODIR)/%,$(_OBJS))

all: server client


server:
	mkdir -p obj
	$(CC) $(LIBS) -c -o $(ODIR)/$@.o $@.cpp
	# $(CC) $(LIBS) obj/state.o obj/server.o -o $@

client: client.cpp
	mkdir -p obj
	$(CC) $(LIBS) -c -o $(ODIR)/$@.o $@.cpp
	# $(CC) $(LIBS) -o $@ obj/client.o

clean:
	rm -rf obj/
