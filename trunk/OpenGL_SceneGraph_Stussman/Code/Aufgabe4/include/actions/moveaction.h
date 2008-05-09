#ifndef _H_MOVEACTION
#define _H_MOVEACTION

#include "actions/actionbase.h"
#include "nodes/movenode.h"

class MoveAction:public ActionBase{
public:
  MoveAction(EDirection aDir, float aDist);
  virtual ~MoveAction();
  virtual void apply();


private:
  EDirection mDir;
  float mDist;
};





#endif // _H_MOVEACTION


