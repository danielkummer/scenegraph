#ifndef _SCENE_H
#define _SCENE_H

#include <SDL.h> 

#include "visitors/visitor.h"
#include "visitors/abstractvisitor.h"
#include "visitors/destructorvisitor.h"
#include "visitors/printvisitor.h"
#include "nodes/allnodes.h"
#include "factories/actionfactory.h"
#include "factories/builder.h"
#include "material.h"


enum EActionNames{
  EActionUnknown = 0,
  EToggleShadow,
  EToggleAxis,
  EToggleFar, // Scheinwerfer Ship
  EToggleTrace, // Planetenbahnen

  EShipShoot,
  EShipMoveFwd,
  EShipMoveBack,
  EShipStrafeLeft,
  EShipStrafeRight,
  EShipMoveUp,
  EShipMoveDown,
  EShipRollClk,
  EShipRollCClk,
  EShipPitchClk,
  EShipPitchCClk,
  EShipYawClk,
  EShipYawCClk,
  
  ECamSwitchType,
  ECamMoveFwd,
  ECamMoveBack,
  ECamStrafeRight,
  ECamStrafeLeft,
  ECamMoveUp,
  ECamMoveDown,
  ECamRollClockwise,
  ECamRollCClockwise,
  ECamPitchClockwise,
  ECamPitchCClockwise,
  ECamYawClockwise,
  ECamYawCClockwise,


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
  bool handleEvent(SDL_Event &aEvent);
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
  virtual ~SolarSytemScene();

  bool handleEvent(SDL_Event &aEvent);
//  void update();
  virtual void init();
//  void quit();

protected:
  void createScene();
  virtual AbstractNode* createPlanet(PlanetDef* aPlanetDef, bool aMoonYesOrNo=true, float aAlpha=1.0f);
  virtual AbstractNode* createPlanet(RingDef* aRingDef);
  AbstractNode* createSolarSystem();
  AbstractNode* createAxis(float aLength=1.0);


};


#endif

