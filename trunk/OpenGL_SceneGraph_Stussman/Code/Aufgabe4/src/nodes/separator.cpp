#include "nodes/separator.h"




//----------------------------------------------------------//
//Separator::Separator():GroupNode(){
//}
//----------------------------------------------------------//
//Separator::~Separator(){
//}
//----------------------------------------------------------//
void Separator::accept(AbstractVisitor &aVisitor){
  aVisitor.visit(*this);
  glPushClientAttrib(GL_CLIENT_ALL_ATTRIB_BITS);
  Separator::visitChildren(aVisitor);
  glPopClientAttrib();
  glColor3f(1, 1, 1);
  aVisitor.postvisit(*this);
}
//----------------------------------------------------------//

