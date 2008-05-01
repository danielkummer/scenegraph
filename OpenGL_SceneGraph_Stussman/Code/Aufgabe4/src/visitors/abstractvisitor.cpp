#include "visitors/abstractvisitor.h"
#include "nodes/abstractnode.h"
#include "nodes/groupnode.h"


//----------------------------------------------------------//
void AbstractVisitor::apply(AbstractNode* aAbstractNode){
  mRootNode = aAbstractNode;
  aAbstractNode->accept(*this);
  mRootNode = 0;
}
//----------------------------------------------------------//

