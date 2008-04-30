#ifndef _H_EVENTVISITOR
#define _H_EVENTVISITOR

class EventVisitor:public AbstractVisitor{
public:
  EventVisitor():AbstractVisitor() { }
  void apply(AbstractNode* aAbstractNode, SDL_Event &aEvent);
  virtual void visit(AbstractNode &aAbstractNode);

private:
  SDL_Event mEvent;
};

#endif // _H_EVENTVISITOR


