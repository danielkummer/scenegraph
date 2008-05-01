#include "nodes/texturenode.h"


//-------------------------------------------------------//
TextureNode::TextureNode(GLint aTexID, GLenum aTarget, bool aBlend):
mTexID(aTexID), mTarget(aTarget), mBlending(aBlend){
}
//-------------------------------------------------------//
inline void TextureNode::accept(AbstractVisitor &aVisitor){
  aVisitor.visit(*this);
}
//-------------------------------------------------------//
