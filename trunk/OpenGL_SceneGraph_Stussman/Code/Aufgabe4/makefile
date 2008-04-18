
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
INCL    = $(GLINCL) $(SDLINCL) 
LIBS    = $(GLLIBS) $(SDLLIB) 


.PHONY: all clean build

SRCFILES=builder.cpp  clock.cpp  draw.cpp  main.cpp  nodes.cpp  planetdefs.cpp  shadow.cpp  visitors.cpp


OBJS=$(SRCFILES:%.cpp=%.o)

####

all : SceneGraphRendnerer

SceneGraphRendnerer : $(OBJS)
	g++ -o $@ $(OBJS) $(LIBS)

%.o : %.cpp
	g++ $(CCFLAGS) $(INCL) -c $<




clean :
	rm *.o

build : clean all
