#ifndef _SCENE_H
#define _SCENE_H

#include <SDL.h> 
#include "visitors/visitors.h"
#include "nodes/nodes.h"
#include "factories/actionfactory.h"
#include "factories/builder.h"


enum EActionNames{
  EActionUnknown = 0,
  EToggleShadow,
  EToggleAxis,
  EToggleFar, // Scheinwerfer Ship
  EToggleTrace, // Planetenbahnen
  EShoot,
  
  ESwitchCamType,


  EToggleGrab,
  EToggleFullscreen,

  EActionNameCount, // just to know the number of items in the enum
};

//-------------------------------------------------------//
//-------------------------------------------------------//

class AbstractScene{
public:
  AbstractScene();
  virtual ~AbstractScene();

  void setActionMap(unsigned aEActionName, unsigned aEAction);
  void setActionMap(unsigned* aEAcitonMap, unsigned aCount);
  void setKeyInputMap(SDLKey aKey, unsigned aEActionName);
  void setKeyInputMap(SDLKey* aKeyMap, unsigned aCount);

  void setSceneGraphRoot(GroupNode* aNode);
  GroupNode* getSeneGraphRoot();

  void setCurrentVisitor(AbstractVisitor* aVisitor);
  AbstractVisitor* getCurrentVisitor();

  // scene specific code
  void handleEvent(SDL_Event &aEvent);
  void update();
  virtual void init();
//  void quit() = 0;

protected:
  void createScene();

  unsigned mToActionMap[EActionNameCount]; // 
  unsigned mKeyInputMap[SDLK_LAST]; // mKeyInputMapt[SDL_KEY] = ActionName

  GroupNode* mSceneGraph;
  Visitor mVisitor;

  ActionFactory* mActionFactory;
  
};

//-------------------------------------------------------//
class SolarSytemScene: public AbstractScene{
public: 
  SolarSytemScene();
//  ~SolarSytemScene();

  void handleEvent(SDL_Event &aEvent);
//  void update();
  virtual void init();
//  void quit();

protected:
  void createScene();




};


#endif

