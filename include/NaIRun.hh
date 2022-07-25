#ifndef NAIRUN_HH
#define NAIRUN_HH

#include "G4UserRunAction.hh"
#include "G4AnalysisManager.hh"
#include "G4Run.hh"

//#include "g4root.hh"
//#include "g4csv.hh"

class NaIRunAction : public G4UserRunAction
{
public:
	NaIRunAction();
	~NaIRunAction();
	virtual void BeginOfRunAction(const G4Run*);
	virtual void EndOfRunAction(const G4Run*);
};

#endif
