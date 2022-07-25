#include "NaIStepping.hh"

NaISteppingAction::NaISteppingAction(NaIEventAction *eventAction)
{
	fEventAction = eventAction;
}

NaISteppingAction::~NaISteppingAction()
{}

void NaISteppingAction::UserSteppingAction(const G4Step *step)
{
	G4LogicalVolume *volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
	
	const NaIDetectorConstruction *detCons = static_cast<const NaIDetectorConstruction*>(G4RunManager::GetRunManager()->GetUserDetectorConstruction());
	
	G4LogicalVolume *fScoringVolume = detCons->GetScoringVolume();
	
	if(volume != fScoringVolume)
	{
		return;
	}
	
	G4double edep = step->GetTotalEnergyDeposit();
	fEventAction->AddEdep(edep);
}
