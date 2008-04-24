#include "actions/actions.h"

//-------------------------------------------------------//
/*********************************************************/
ActionBase::~ActionBase(){
}
//-------------------------------------------------------//
inline void ActionBase::accept(AbstractVisitor &aVisitor){
  aVisitor.visit(*this);
}
//-------------------------------------------------------//
//-------------------------------------------------------//
//-------------------------------------------------------//
//-------------------------------------------------------//
//-------------------------------------------------------//
