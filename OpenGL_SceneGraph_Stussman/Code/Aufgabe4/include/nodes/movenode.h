#ifndef _H_MOVENODE
#define _H_MOVENODE

#include "nodes/abstractnode.h"

enum EDirection{
  UP,
  DOWN,
  LEFT,
  RIGHT,
  FORWARD,
  BACKWARD,
};

enum EAxis{
  ROLL,
  YAW,
  PITCH,
  ROLLCC,
  YAWCC,
  PITCHCC,
};


class MoveNode:public AbstractNode{
public:
  MoveNode();
  virtual ~MoveNode();

  virtual void accept(AbstractVisitor &aVisitor);
  // accumulating functions
  virtual void move(EDirection aDir, float aDist);
  virtual void rotate(EAxis aAxis, float aAngle);

  float getX();
  float getY();
  float getZ();
  float getRoll();
  float getYaw();
  float getPitch();
  // reset values
  void reset();
  // if position or rotation has changed
  bool getChanged();
  void setChanged(bool aYesOrNo);

  // is only for applying actions
  void activate();
  void deactivate();
  bool isActive();

private:
  float mDeltaX;
  float mDeltaY;
  float mDeltaZ;

  float mDeltaRoll;
  float mDeltaYaw;
  float mDeltaPitch;

  bool mChanged;

  bool mActive;


};


#endif // _H_MOVENODE


