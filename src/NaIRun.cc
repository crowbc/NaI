#include "NaIRun.hh"

NaIRunAction::NaIRunAction()
{
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	
	man->CreateNtuple("MCTruth", "MCTruth");
	man->CreateNtupleIColumn("fEvent");// col 0
	man->CreateNtupleDColumn("fX");// col 1
	man->CreateNtupleDColumn("fY");// col 2
	man->CreateNtupleDColumn("fZ");// col 3
	man->CreateNtupleDColumn("fT");// col 4
	man->CreateNtupleDColumn("fWlen");// col 5
	man->CreateNtupleDColumn("fPX0");// col 6
	man->CreateNtupleDColumn("fPY0");// col 7
	man->CreateNtupleDColumn("fPZ0");// col 8
	//man->CreateNtupleDColumn("fEdep");
	man->FinishNtuple(0);
	
	man->CreateNtuple("Hits", "Hits");
	man->CreateNtupleIColumn("fEvent");
	//man->CreateNtupleIColumn("peHits");
	man->FinishNtuple(1);
	
	man->CreateNtuple("Scoring", "Scoring");
	man->CreateNtupleDColumn("fEdep");
	man->FinishNtuple(2);
}

NaIRunAction::~NaIRunAction()
{}

void NaIRunAction::BeginOfRunAction(const G4Run* NaIRun)
{
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	G4int rNum = NaIRun->GetRunID();
	std::stringstream sRunID;
	sRunID << rNum;
	G4String name = "NaIoutput";
	G4String ext = ".root";
	G4String fName = name + sRunID.str() + ext;
	man->OpenFile(fName);
	man->SetVerboseLevel(1);
}

void NaIRunAction::EndOfRunAction(const G4Run*)
{
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	
	man->Write();
	man->CloseFile();
}
