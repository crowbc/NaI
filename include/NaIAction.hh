#ifndef NAIACTION_HH
#define NAIACTION_HH

#include "G4VUserActionInitialization.hh"

#include "NaIGenerator.hh"
#include "NaIRun.hh"
#include "NaIEvent.hh"
#include "NaIStepping.hh"

class NaIActionInitialization : public G4VUserActionInitialization
{
public:
	NaIActionInitialization();
	~NaIActionInitialization();
	
	virtual void Build() const;
	virtual void BuildForMaster() const;
};

#endif
