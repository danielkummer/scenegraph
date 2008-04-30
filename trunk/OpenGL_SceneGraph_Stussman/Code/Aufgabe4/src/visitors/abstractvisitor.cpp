#include "visitors/abstractvisitor.h"


//----------------------------------------------------------//
void AbstractVisitor::apply(AbstractNode* aAbstractNode){
  mRootNode = aAbstractNode;
  aAbstractNode->accept(*this);
  mRootNode = NULL;
}
//----------------------------------------------------------//

