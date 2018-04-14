CC=g++
LIBS=-std=c++11 -lsfml-window -lsfml-network -lsfml-graphics -lsfml-system -lBox2D
SUBDIRS=Logic network

all: $(SUBDIRS)
	$(CC) $(LIBS) -o poball main.cpp Logic/obj/*

$(SUBDIRS):
		$(MAKE) -C $@
clean: $(SUBDIRS)
	$(MAKE) -C $@ 
	rm poball

.PHONY: all $(SUBDIRS)
