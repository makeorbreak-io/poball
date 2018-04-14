CC=g++
LIBS=-std=c++11 -lsfml-window -lsfml-network -lsfml-graphics -lsfml-system -lBox2D
SUBDIRS=Logic network

all: $(SUBDIRS)
	$(CC) $(LIBS) -o poball main.cpp Logic/obj/*

clean:

$(SUBDIRS):
		$(MAKE) -C $@

clean:
	$(MAKE) -C Logic $(MAKECMDGOALS)
	$(MAKE) -C network $(MAKECMDGOALS)
	rm poball

.PHONY: all $(SUBDIRS)
