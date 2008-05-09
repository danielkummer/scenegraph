#include "visitors/destructorvisitor.h"


//----------------------------------------------------------//
DestructorVisitor::DestructorVisitor():AbstractVisitor(){
}
//----------------------------------------------------------//
DestructorVisitor::~DestructorVisitor(){
}
//----------------------------------------------------------//
inline void DestructorVisitor::visit(AbstractNode &aNode){
}
//----------------------------------------------------------//
inline void DestructorVisitor::postvisit(AbstractNode &aNode){
}
//----------------------------------------------------------//
void DestructorVisitor::postvisit(GroupNode &aNode){
  aNode.clear();
}
//----------------------------------------------------------//
void DestructorVisitor::visit(TransformSeparator &aNode){
}
//----------------------------------------------------------//
void DestructorVisitor::postvisit(TransformSeparator &aNode){
  aNode.clear();
}
//----------------------------------------------------------//
void DestructorVisitor::postvisit(Separator &aNode){
  aNode.clear();
}
//----------------------------------------------------------//
void DestructorVisitor::visit(ToggleNode &aNode){
  aNode.on();
}
//----------------------------------------------------------//
void DestructorVisitor::postvisit(ToggleNode &aNode){
  aNode.clear();
}
//----------------------------------------------------------//
void DestructorVisitor::visit(TextureNode &aNode){
  glDeleteTextures(1, &(aNode.mTexID));
}
//----------------------------------------------------------//

