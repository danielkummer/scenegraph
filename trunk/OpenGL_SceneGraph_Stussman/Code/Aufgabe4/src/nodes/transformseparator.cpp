#include "nodes/transformseparator.h"


//----------------------------------------------------------//
void TransformSeparator::accept(AbstractVisitor &aVisitor){
  aVisitor.visit(*this);
  TransformSeparator::visitChildren(aVisitor);
  aVisitor.postvisit(*this);
}
//----------------------------------------------------------//

