#ifndef _CLOCK_H
#define _CLOCK_H

#include <vector>
#include <SDL.h>

class ClockListener{
public:
  ClockListener() { }
  virtual ~ClockListener() { }

  virtual void update(float dt, double time) = 0;

};
//-------------------------------------------------------//
class Clock{

public:
  Clock():mTime(0), mDilatation(1.0), mListeners() { }
  ~Clock();

  void tick();
  void setDilatation(float aFactor);
  float getDilatation();

  void addListener(ClockListener* aListener);
  void removeListener(ClockListener* aListener);

  static Clock* getDefaultClock();

protected:
  static Clock* mDefaultClock;

private:
  double mTime;
  long mOldNow;
  float mDilatation;
  std::vector<ClockListener*> mListeners;;


};

#endif
