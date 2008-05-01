#ifndef _H_STARSNODE
#define _H_STARSNODE

class StarsNode:public AbstractNode{
public:
  StarsNode(float aRadiusMin, float aDeltaR, unsigned aNumStars);
  virtual ~StarsNode() { delete[] mVertices; }
  virtual void accept(AbstractVisitor &aVisitor);

  float mRadiusMin;
  float mDeltaR;
  unsigned mNumStars;
  float* mVertices;
};

#endif // _H_STARSNODE


