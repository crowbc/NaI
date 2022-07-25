#ifndef NAIDETECTOR_HH
#define NAIDETECTOR_HH

#include "G4VSensitiveDetector.hh"
#include "G4RunManager.hh"
#include "G4AnalysisManager.hh"
#include "G4SystemOfUnits.hh"

//#include "g4root.hh"
//#include "g4csv.hh"

class NaISensitiveDetector : public G4VSensitiveDetector
{
public:
	NaISensitiveDetector(G4String);
	~NaISensitiveDetector();
	
private:
	virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *);
	const G4double HCNM = 1.239841939*keV;
	
	//G4PhysicsOrderedFreeVector *quEff;// doesn't compile as G4PhysicsOrderedFreeVector
};

#endif
