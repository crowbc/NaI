#include "NaIDetector.hh"

NaISensitiveDetector::NaISensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{
	//quEff = new G4PhysicsOrderedFreeVector();// doesn't compile if specified as G4PhysicsOrderedFreeVector()
}

NaISensitiveDetector::~NaISensitiveDetector()
{}

G4bool NaISensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *R0hist)
{
	G4Track *track = aStep->GetTrack();
	
	track->SetTrackStatus(fStopAndKill);
	
	G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
	G4StepPoint *postStepPoint = aStep->GetPostStepPoint();
	
	G4ThreeVector posPhoton = preStepPoint->GetPosition();
	G4ThreeVector momPhoton = preStepPoint->GetMomentum();
	
	//G4cout << "Photon position: " << posPhoton << G4endl;
	
	G4double wlen = HCNM/momPhoton.mag();
	
	const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();
	G4int copyNo = touchable->GetCopyNumber();// should always be 0 for this detector
	
	//G4cout << "Detector index: " << copyNo <<  G4endl;
	
	G4VPhysicalVolume *physVol = touchable->GetVolume();
	G4ThreeVector posDetector = physVol->GetTranslation();
	
	//G4cout << "Detector position: " << posDetector << G4endl;// should always be position of PMT sensitive region
	
	G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
	
	G4AnalysisManager* man = G4AnalysisManager::Instance();
	
	man->FillNtupleIColumn(0, 0, evt);
	man->FillNtupleDColumn(0, 1, posPhoton[0]);
	man->FillNtupleDColumn(0, 2, posPhoton[1]);
	man->FillNtupleDColumn(0, 3, posPhoton[2]);
	man->FillNtupleDColumn(0, 4, wlen);
	man->AddNtupleRow(0);
	
	man->FillNtupleIColumn(1, 0, evt);
	man->AddNtupleRow(1);
	
	return true;
}
