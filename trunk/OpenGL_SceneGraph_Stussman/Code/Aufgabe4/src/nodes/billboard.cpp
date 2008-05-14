#include "nodes/billboard.h"


Billboard::Billboard(float aWidth, float aHeight, float aNormX, float aNormY, float aNormZ, int aTexID):
mWidth(aWidth), mHeight(aHeight), mNormX(aNormX), mNormY(aNormY), mNormZ(aNormZ), mTexID(aTexID){

}
//----------------------------------------------------------//
Billboard::~Billboard(){

}
//----------------------------------------------------------//
void Billboard::accept(AbstractVisitor &aVisitor){
  aVisitor.visit(*this);
}
//----------------------------------------------------------//
//----------------------------------------------------------//



