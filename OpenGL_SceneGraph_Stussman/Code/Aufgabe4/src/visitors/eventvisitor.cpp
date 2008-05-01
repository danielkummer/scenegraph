#include "visitors/eventvisitor.h"


//----------------------------------------------------------//
void EventVisitor::apply(AbstractNode* aAbstractNode, SDL_Event &aEvent){
  mEvent = aEvent;
  AbstractVisitor::apply(aAbstractNode);
}
//----------------------------------------------------------//
/*void EventVisitor::visit(AbstractNode &aAbstractNode){
  switch(aAbstractNode.mBeh){
    case eBeh1:{
      switch(mEvent.type){
        case SDL_KEYDOWN:{
          switch(mEvent.key.keysym.sym){
            case SDLK_F1:{
              // code 
            }
            break;
            case SDLK_F2:{
              // code 
            }
            break;

          }
        }
      }
    }
    break;
  }
}
//----------------------------------------------------------//
*/


