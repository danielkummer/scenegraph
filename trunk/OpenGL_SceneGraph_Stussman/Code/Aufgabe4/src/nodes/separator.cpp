#include "nodes/separator.h"


//----------------------------------------------------------//
void Separator::accept(AbstractVisitor &aVisitor){
  aVisitor.visit(*this);
}
//----------------------------------------------------------//

