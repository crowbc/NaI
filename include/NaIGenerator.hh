#ifndef NAIGENERATOR_HH
#define NAIGENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"

#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "G4Geantino.hh"
#include "G4IonTable.hh"

class NaIPrimaryGenerator : public G4VUserPrimaryGeneratorAction
{
public:
	NaIPrimaryGenerator();
	~NaIPrimaryGenerator();
	
	virtual void GeneratePrimaries(G4Event*);
	
private:
	G4ParticleGun* fParticleGun;
};

#endif
