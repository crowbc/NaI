#include "NaIEvent.hh"

NaIEventAction::NaIEventAction(NaIRunAction*)
{
	fEdep = 0.;
}

NaIEventAction::~NaIEventAction()
{}

void NaIEventAction::BeginOfEventAction(const G4Event*)
{
	fEdep = 0.;
}

void NaIEventAction::EndOfEventAction(const G4Event*)
{
	//G4cout << "Energy deposition: " << fEdep << " MeV" << G4endl;
	
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	
	man->FillNtupleDColumn(2, 0, fEdep);
	man->AddNtupleRow(2);
}
