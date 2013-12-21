COMPILER=g++
MACHINE=$(shell uname -s)
CFLAGS=-I. -Wall -m64 -pthread -std=c++11 -g
LIBRARIES=-lm -lGLEW -lGL -lGLU -lglut
OBJDIR=.obj
SOURCES=jengine.cc main.cc
DEPENDENCIES=jengine.h custom_config.h
BINARY=play

#################################################

OBJ = $(patsubst %,$(OBJDIR)/%.o,$(SOURCES))

$(OBJDIR)/%.o: % $(DEPENDENCIES)
	$(COMPILER) -c -o $@ $< $(CFLAGS)

$(BINARY): $(OBJ)
	$(COMPILER) -o $@ $^ $(CFLAGS) $(LIBRARIES)

.PHONY: clean

clean:
	rm -f $(BINARY) $(OBJDIR)/*.o *~ core
