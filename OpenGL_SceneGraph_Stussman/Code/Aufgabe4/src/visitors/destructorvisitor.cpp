#include "visitors/destructorvisitor.h"


//----------------------------------------------------------//
void DestructorVisitor::postvisit(GroupNode &aGroupNode){
  aGroupNode.clear();
}
//----------------------------------------------------------//
void DestructorVisitor::postvisit(TransformSeparator &aTransformSep){
  aTransformSep.clear();
}
//----------------------------------------------------------//
void DestructorVisitor::visit(TextureNode &aNode){
  glDeleteTextures(1, &(aNode.mTexID));
}
//----------------------------------------------------------//

