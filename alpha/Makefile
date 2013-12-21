COMPILER=g++
MACHINE=$(shell uname -s)
CFLAGS=-I. -Wall -m64 -pthread -std=c++11 -g
LIBRARIES=-lm -lGLEW -lGL -lGLU -lglut
OBJDIR=.obj
SOURCES=user_interface.cc entity.cc render.cc filter.cc scene.cc jengine.cc custom_scene.cc main.cc
DEPENDENCIES=math.h toolbox.h user_interface.h entity.h render.h filter.h scene.h jengine.h custom_scene.h custom_config.h
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
