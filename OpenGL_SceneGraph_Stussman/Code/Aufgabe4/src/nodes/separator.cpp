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
  Separator::visitChildren(aVisitor);
  aVisitor.postvisit(*this);
}
//----------------------------------------------------------//

