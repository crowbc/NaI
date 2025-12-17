#include "NaIEvent.hh"

NaIEventAction::NaIEventAction(NaIRunAction*)
{
	fEdep = 0.;
}

NaIEventAction::~NaIEventAction()
{}

void NaIEventAction::BeginOfEventAction(const G4Event* anEvent)
{
	fEdep = 0.;
}

void NaIEventAction::EndOfEventAction(const G4Event* anEvent)
{
	//G4cout << "Energy deposition: " << fEdep << " MeV" << G4endl;
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	fEvent = anEvent->GetEventID();
	man->FillNtupleIColumn(2, 0, fEvent);
	man->FillNtupleDColumn(2, 1, fEdep);
	man->AddNtupleRow(2);
}
