COMPILER=g++
MACHINE=$(shell uname -s)
CFLAGS=-I. -Wall -m64 -pthread -std=c++11 -g
LIBRARIES=-lm -lGLEW -lGL -lGLU -lglut
OBJDIR=.obj
SOURCES=user_interface.cc render.cc shader.cc mesh.cc entity.cc shape.cc camera.cc filter.cc scene.cc jengine.cc custom_scene.cc main.cc
DEPENDENCIES=vmath.h toolbox.h user_interface.h render.h shader.h mesh.h entity.h shape.cc camera.h filter.h scene.h jengine.h custom_scene.h custom_config.h
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
