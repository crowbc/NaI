#include "NaIStepping.hh"

NaISteppingAction::NaISteppingAction(NaIEventAction *eventAction)
{
	fEventAction = eventAction;
}

NaISteppingAction::~NaISteppingAction()
{}

void NaISteppingAction::UserSteppingAction(const G4Step *step)
{
	G4double edep = 0;
	// determine what was hit
	G4LogicalVolume *volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
	// get the scoring volume
	const NaIDetectorConstruction *detCons = static_cast<const NaIDetectorConstruction*>(G4RunManager::GetRunManager()->GetUserDetectorConstruction());
	G4LogicalVolume *fScoringVolume = detCons->GetScoringVolume();
	// determine what hit the volume
	G4String pName = step->GetTrack()->GetDefinition()->GetParticleName();
	G4int pID = ParticleNameToIDNumber(pName);
	if(volume != fScoringVolume)
	{
		// break if scoring volume wasn't hit
		return;
	}
	//if(pID != 100){
		// don't count optical photon energy - disabled conditional. Now counting everything
		edep = step->GetTotalEnergyDeposit();
	//}
	fEventAction->AddEdep(edep);
}
// Particle Name to ID number converter
G4int NaISteppingAction::ParticleNameToIDNumber(G4String name)
{
	G4int num;
	if(name == "gamma"){
		num=1;
	}
	else if(name == "e"){
		num=2;
	}
	else if(name == "e+"){
		num=3;
	}
	else if(name == "neutron"){
		num=4;
	}
	else if(name == "proton"){
		num=5;
	}
	else if(name == "mu+"){
		num=6;
	}
	else if(name == "mu-"){
		num=7;
	}
	else if(name == "alpha"){
		num=8;
	}
	else if(name == "Li7"){
		num=9;
	}
	else if(name == "opticalphoton"){
		num=100;
	}
	else num=0;
	return num;
}
