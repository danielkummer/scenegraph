#include "nodes/texturenode.h"


//-------------------------------------------------------//
TextureNode::TextureNode(GLint aTexID, GLenum aTarget, bool aBlend):
mTexID(aTexID), mTarget(aTarget), mBlending(aBlend){
}
//-------------------------------------------------------//
TextureNode::TextureNode(GLint aTexID, GLenum aSFactor, GLenum aDFactor,  GLenum aTarget):
mBlending(true), mSFactor(aSFactor), mDFactor(aDFactor), mTexID(aTexID), mTarget(aTarget){
}
//-------------------------------------------------------//
inline void TextureNode::accept(AbstractVisitor &aVisitor){
  aVisitor.visit(*this);
}
//-------------------------------------------------------//
