#ifndef _ONOFF_ACTION_H
#define _ONOFF_ACTION_H

#include "actions/actionbase.h"
#include "visitors/abstractvisitor.h"
#include "nodes/togglenode.h"
#include "nodes/abstractnode.h"

//-------------------------------------------------------//
class OnOffAction:public ActionBase{
public:
  virtual ~OnOffAction();
  virtual void apply();
//  virtual void accept(AbstractVisitor &aVisitor);
  virtual void add(ToggleNode* aToggle);
  void on();
  void off();
  void toggle();
  bool isOn();
private:
  bool mOn;
};
//-------------------------------------------------------//



#endif // _ONOFF_ACTION_H

