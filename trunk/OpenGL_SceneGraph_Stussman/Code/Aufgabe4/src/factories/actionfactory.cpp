#include "factories/actionfactory.h"
#include <assert.h>



ActionFactory::ActionFactory(unsigned int *aActionMapping, unsigned int aCount){
  mMapping = new unsigned[aCount];
  mActionInstances = new ActionBase*[aCount];
  // copy mapping and init instances
  for(unsigned i=0; i<aCount; i++){
    mMapping[i] = aActionMapping[i];
    mActionInstances[i] = NULL;
  }
  mCount = aCount;
}
//-------------------------------------------------------//
ActionFactory::~ActionFactory(){
  delete[] mMapping;
  for(unsigned i=0; i<mCount; i++){
    delete mActionInstances[i];
  }
  delete[] mActionInstances;
}
//-------------------------------------------------------//
ActionBase* ActionFactory::getAction(unsigned int aActionName){
  assert(mCount > aActionName);
  if(NULL == mActionInstances[aActionName]){
    mActionInstances[aActionName] = createAction(aActionName);
  }
  assert(NULL != mActionInstances[aActionName]);
  return mActionInstances[aActionName];
}
//-------------------------------------------------------//
ActionBase* ActionFactory::createAction(unsigned int aActionName){
  assert(mCount > aActionName);
  unsigned vActionNr = mMapping[aActionName];
  ActionBase* vInstance = NULL;
  switch(vActionNr){
    // TODO: insert all new actions
    case EToggleAction:
      {
        vInstance = new OnOffAction();
      }break;
  }
  return vInstance;

}
//-------------------------------------------------------//
//-------------------------------------------------------//
