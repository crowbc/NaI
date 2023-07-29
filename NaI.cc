// This code is for the NaI detector example simulation

// Included C++ libraries

#include <iostream>
#include <fstream>

// Included Geant4 libriaries

#include "G4RunManagerFactory.hh"
#include "G4MTRunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

// Included simulation libraries
#include "NaIDetectorConstruction.hh"
#include "NaIPhysics.hh"
#include "NaIAction.hh"

int main(int argc, char** argv)
{
	// define UI session
	G4UIExecutive *ui = 0;
	
	#ifdef G4MULTITHREADED
		G4MTRunManager *runManager = new G4MTRunManager();
		// set mandatory initialization classes
		runManager->SetUserInitialization(new NaIDetectorConstruction());
		runManager->SetUserInitialization(new NaIPhysicsList());
		runManager->SetUserInitialization(new NaIActionInitialization());
		// put "/run/numberOfThreads <N>" in macro file, where <N> is the number of cores to use in simulation
		// put "/run/initialize" in macro file
	#else
		// construct the default run manager
		G4RunManager *runManager = new G4RunManager();
		// set mandatory initialization classes
		runManager->SetUserInitialization(new NaIDetectorConstruction());
		runManager->SetUserInitialization(new NaIPhysicsList());
		runManager->SetUserInitialization(new NaIActionInitialization());
		// initialize G4 kernel
		runManager->Initialize();
	#endif
	
	G4String macCmd = "/control/execute ";
	G4String macName = "init_vis.mac";
	
	if(argc==1)
	{
		ui = new G4UIExecutive(argc, argv);
	}
	
	// construct the visualization manager
	G4VisManager *visManager = new G4VisExecutive();
	visManager->Initialize();
	
	// get the pointer to the UI manager and define session
	G4UImanager *UImanager = G4UImanager::GetUIpointer();
	
	if(ui)
	{
		// open viewer, set default view and draw the geometry and particle events
		UImanager->ApplyCommand(macCmd+macName);
		ui->SessionStart();	
	}
	else
	{
		macName=argv[1];
		UImanager->ApplyCommand(macCmd+macName);
	}
	
	// job termination
	delete runManager;
	delete visManager;
	delete ui;
	return 0;
}
