
REENTRANT = -D_REENTRANT


############################################
# OpenGL Stuff
############################################

GLDIR   = /usr
GLINCL  = -I$(GLDIR)/include/GL
GLLIBS  = -L$(GLDIR)/lib -lGL -lGLU $(GL_LIBS)


############################################
# SDL Stuff
############################################


SDLINCL  = -I/usr/include/SDL
SDLLIB  = -L/usr/lib -lSDL 
#-lSDL_ttf


############################################
# Compiler Stuff
############################################

X11LIBS = -L/usr/X11R6/lib
CCFLAGS = $(REENTRANT) $(POSIX) $(CFLAGS) -Wall -g
INCL    = $(GLINCL) $(SDLINCL) -Iinclude
LIBS    = $(GLLIBS) $(SDLLIB) 


.PHONY: all clean build

SRCFILES=src/clock.cpp src/main.cpp src/planetdefs.cpp src/nodes/nodes.cpp src/shadow.cpp src/factories/builder.cpp src/draw.cpp src/visitors/visitors.cpp src/factories/actionfactory.cpp src/actions/onoffaction.cpp src/actions/actions.cpp src/scene.cpp src/material.cpp


OBJS=$(SRCFILES:%.cpp=%.o)

####

all : dep SceneGraphRendnerer

SceneGraphRendnerer : $(OBJS)
	g++ -o $@ $(OBJS) $(LIBS)

%.o : %.cpp
	g++ $(CCFLAGS) $(INCL) -c $< -o $@

dep: 
	makedepend -- $(CCFLAGS) $(INCL) -- $(SRCFILES) 2>/dev/null

clean :
	rm $(OBJS) SceneGraphRendnerer 2>/dev/null
	

build : clean all

# DO NOT DELETE

