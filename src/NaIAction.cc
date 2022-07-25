#include "NaIAction.hh"

NaIActionInitialization::NaIActionInitialization()
{}

NaIActionInitialization::~NaIActionInitialization()
{}

void NaIActionInitialization::BuildForMaster() const
{
	NaIRunAction *runAction = new NaIRunAction();
	SetUserAction(runAction);
}

void NaIActionInitialization::Build() const
{
	NaIPrimaryGenerator *generator = new NaIPrimaryGenerator();
	SetUserAction(generator);
	
	NaIRunAction *runAction = new NaIRunAction();
	SetUserAction(runAction);
	
	NaIEventAction *eventAction = new NaIEventAction(runAction);
	SetUserAction(eventAction);
	
	NaISteppingAction *steppingAction = new NaISteppingAction(eventAction);
	SetUserAction(steppingAction);
}
