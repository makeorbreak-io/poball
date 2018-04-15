CC=g++
LIBS=-std=c++11 -lsfml-window -lsfml-network -lsfml-graphics -lsfml-system -lBox2D -g

ODIR=obj
SRC=$(wildcard *.cpp)
OBJS=$(patsubst %.cpp, $(ODIR)/%.o, $(SRC))

all: $(OBJS)

$(ODIR)/game.o: game.cpp
		$(CC) $(LIBS) -I../network/ -c -o $@ $^ ../network/obj/client.o

$(ODIR)/%.o: %.cpp
		mkdir -p obj
		$(CC) $(LIBS) -c -o $@ $^

clean:
	rm -rf obj
