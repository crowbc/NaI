#ifndef NAIEVENT_HH
#define NAIEVENT_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "G4AnalysisManager.hh"

//#include "g4root.hh"
//#include "g4csv.hh"

#include "NaIRun.hh"

class NaIEventAction : public G4UserEventAction
{
public:
	NaIEventAction(NaIRunAction*);
	~NaIEventAction();
	
	virtual void BeginOfEventAction(const G4Event*);
	virtual void EndOfEventAction(const G4Event*);
	
	void AddEdep(G4double edep){ fEdep+=edep; }
private:
	G4double fEdep;
};

#endif
