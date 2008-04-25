INCLUDES = -I$(top_srcdir)/include $(SDL_CFLAGS) \
			$(GL_INCLUDEDIR)


bin_PROGRAMS=SceneGraph
SceneGraph_SOURCES=clock.cpp main.cpp planetdefs.cpp material.cpp nodes/nodes.cpp actions/onoffaction.cpp actions/actions.cpp scene.cpp shadow.cpp factories/actionfactory.cpp factories/builder.cpp draw.cpp visitors/visitors.cpp
SceneGraph_LDADD = $(SDL_LIBS) $(GL_LIBS)
