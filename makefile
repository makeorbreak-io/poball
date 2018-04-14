CC=g++
LIBS=-std=c++11 -lsfml-window -lsfml-network -lsfml-graphics -lsfml-system -lBox2D
SUBDIRS=Logic network

all: $(SUBDIRS)
	$(CC) $(LIBS) -o game main.cpp

$(SUBDIRS):
		$(MAKE) -C $@

.PHONY: all $(SUBDIRS)
