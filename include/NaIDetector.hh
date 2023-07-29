#ifndef NAIDETECTOR_HH
#define NAIDETECTOR_HH

#include "G4VSensitiveDetector.hh"
#include "G4RunManager.hh"
#include "G4AnalysisManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4HCofThisEvent.hh"
#include "G4TouchableHistory.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include "G4TrackingManager.hh"
#include "G4EventManager.hh"

class NaISensitiveDetector : public G4VSensitiveDetector
{
public:
	NaISensitiveDetector(G4String);
	~NaISensitiveDetector();
	virtual G4int ParticleNameToIDNumber(G4String name);
private:
	virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *);
	const G4double HCNM = 1.239841939*keV;
	//G4PhysicsOrderedFreeVector *quEff;// doesn't compile as G4PhysicsOrderedFreeVector
};

#endif
