#include "nodes/transformseparator.h"


//----------------------------------------------------------//
void TransformSeparator::accept(AbstractVisitor &aVisitor){
  aVisitor.visit(*this);
  glPushMatrix();
  TransformSeparator::visitChildren(aVisitor);
  glPopMatrix();
  aVisitor.postvisit(*this);
}
//----------------------------------------------------------//

