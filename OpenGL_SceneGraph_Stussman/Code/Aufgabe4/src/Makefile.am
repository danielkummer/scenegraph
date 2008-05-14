INCLUDES = -I$(top_srcdir)/include $(SDL_CFLAGS) \
			$(GL_INCLUDEDIR) $(GLU_INCLUDEDIR)


bin_PROGRAMS=SceneGraph
SceneGraph_LDADD = $(SDL_LIBS) $(GL_LIBS) $(GLU_LIBS)

SceneGraph_SOURCES= \
actions/rotationaction.cpp \
actions/onoffaction.cpp \
actions/moveaction.cpp \
actions/actionbase.cpp \
clock.cpp \
draw.cpp \ 
factories/actionfactory.cpp \
factories/builder.cpp \
factories/TextureManager.cpp \
factories/ObjLoader.cpp \
main.cpp \
material.cpp \
nodes/starsnode.cpp \
nodes/togglenode.cpp \
nodes/lightnode.cpp \
nodes/linenode.cpp \
nodes/movenode.cpp \
nodes/transformseparator.cpp \
nodes/polygonObjectNode.cpp \
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
nodes/translatornode.cpp \
nodes/separator.cpp \
nodes/scalenode.cpp \
nodes/scalatornode.cpp \
nodes/destructornode.cpp \
nodes/cam.cpp	\
nodes/billboard.cpp \
planetdefs.cpp \
scene.cpp \
shadow.cpp \
visitors/eventvisitor.cpp \
visitors/printvisitor.cpp \
visitors/abstractvisitor.cpp \
visitors/visitor.cpp 

