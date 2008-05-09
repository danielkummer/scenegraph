INCLUDES = -I$(top_srcdir)/include $(SDL_CFLAGS) \
			$(GL_INCLUDEDIR) $(GLU_INCLUDEDIR)


bin_PROGRAMS=SceneGraph
SceneGraph_LDADD = $(SDL_LIBS) $(GL_LIBS) $(GLU_LIBS)

SceneGraph_SOURCES= \
actions/onoffaction.cpp \
actions/actionbase.cpp \
clock.cpp \
draw.cpp \
factories/actionfactory.cpp \
factories/builder.cpp \
factories/ObjLoader.cpp \
main.cpp \
material.cpp \
nodes/togglenode.cpp \
nodes/lightnode.cpp \
nodes/linenode.cpp \
nodes/scalenode.cpp \
nodes/transformseparator.cpp \
nodes/translationnode.cpp \
nodes/groupnode.cpp \
nodes/materialnode.cpp \
nodes/rotationnode.cpp \
nodes/rotornode.cpp \
nodes/shadownode.cpp \
nodes/spherenode.cpp \
nodes/switchnode.cpp \
nodes/ringnode.cpp \
nodes/texturenode.cpp \
nodes/colornode.cpp \
nodes/abstractnode.cpp \
nodes/separator.cpp \
nodes/starsnode.cpp \
nodes/movenode.cpp \
nodes/polygonObjectNode.cpp \
planetdefs.cpp \
scene.cpp \
shadow.cpp \
visitors/destructorvisitor.cpp \
visitors/eventvisitor.cpp \
visitors/printvisitor.cpp \
visitors/abstractvisitor.cpp \
visitors/visitor.cpp

#nodes/_old_nodes.cpp 

#visitors/_old_visitors.cpp
#actions/_old_actions.cpp 
