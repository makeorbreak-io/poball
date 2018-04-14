CC=g++
LIBS=-std=c++11 -lsfml-window -lsfml-network -lsfml-graphics -lsfml-system -lBox2D

ODIR=obj
SRC=$(wildcard *.cpp)
OBJS=$(patsubst %.cpp, $(ODIR)/%.o, $(SRC))

all: $(OBJS)

$(ODIR)/%.o: %.cpp
		mkdir -p obj
		$(CC) $(LIBS) -c -o $@ $^

clean:
	rm -rf obj
