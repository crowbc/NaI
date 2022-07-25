#include "NaIRun.hh"

NaIRunAction::NaIRunAction()
{
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	
	man->CreateNtuple("Photon", "Photon");
	man->CreateNtupleIColumn("fEvent");
	man->CreateNtupleDColumn("fX");
	man->CreateNtupleDColumn("fY");
	man->CreateNtupleDColumn("fZ");
	man->CreateNtupleDColumn("fWlen");
	man->FinishNtuple(0);
	
	man->CreateNtuple("Hits", "Hits");
	man->CreateNtupleIColumn("fEvent");
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
