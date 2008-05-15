#ifndef _ONOFF_ACTION_H
#define _ONOFF_ACTION_H

#include "actions/actionbase.h"
#include "visitors/abstractvisitor.h"
#include "nodes/togglenode.h"
#include "nodes/abstractnode.h"
#include "nodes/togglenode.h"

//-------------------------------------------------------//
class OnOffAction:public ActionBase{
public:
  virtual ~OnOffAction();
  OnOffAction();
  virtual void fire();
  virtual void fire(float aVal);
//  virtual void accept(AbstractVisitor &aVisitor);
  void add(AbstractNode* aToggle);
  void on();
  void off();
  void toggle();
  bool isOn();

protected:
  std::vector<ToggleNode*> mListeners;

private:
  bool mOn;
};
//-------------------------------------------------------//



#endif // _ONOFF_ACTION_H

