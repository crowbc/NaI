#ifndef NAIPHYSICS_HH
#define NAIPHYSICS_HH

#include "G4VModularPhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4OpticalPhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"

class NaIPhysicsList : public G4VModularPhysicsList
{
public:
	NaIPhysicsList();
	~NaIPhysicsList();
};

#endif
