#ifndef NAISTEPPING_HH
#define NAISTEPPING_HH

#include "G4UserSteppingAction.hh"
#include "G4Step.hh"

#include "NaIDetectorConstruction.hh"
#include "NaIEvent.hh"

class NaISteppingAction : public G4UserSteppingAction
{
public:
	NaISteppingAction(NaIEventAction* eventAction);
	~NaISteppingAction();
	
	virtual void UserSteppingAction(const G4Step*);
	
private:
	NaIEventAction *fEventAction;
};

#endif
