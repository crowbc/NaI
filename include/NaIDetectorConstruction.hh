//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file NaIDetectorConstruction.hh
/// \brief Definition of the NaIDetectorConstruction class

#ifndef NAIDETECTORCONSTRUCTION_HH
#define NAIDETECTORCONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
//#include "G4UnitDefinition.hh"
#include "G4Box.hh"
//#include "G4Cons.hh"
//#include "G4Orb.hh"
//#include "G4Sphere.hh"
//#include "G4Trd.hh"
#include "G4Tubs.hh"
#include "G4GenericMessenger.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalSkinSurface.hh"

#include "NaIDetector.hh"

class NaIDetectorConstruction : public G4VUserDetectorConstruction
{
public:
	NaIDetectorConstruction();
	~NaIDetectorConstruction();
	
	G4LogicalVolume *GetScoringVolume() const { return fScoringVolume; }
	
	virtual G4VPhysicalVolume* Construct();
	
private:
	G4Box *wBox;
	G4Tubs *solidDetector, *bottom, *barrel, *flange, *crystal;
	G4LogicalVolume *logicWorld, *logicDetector, *logicBottom, *logicBarrel, *logicFlange, *logicCrystal;
	G4VPhysicalVolume *physWorld, *physDetector, *physBottom, *physBarrel, *physFlange, *physCrystal;
	
	G4OpticalSurface *mirrorSurface;
	G4LogicalSkinSurface *skinBarrel, *skinBottom;
	
	G4Material *wMat, *AlMat, *NaI;
	G4Element *Al, *Na, *I;
	G4MaterialPropertiesTable *mptAl, *mptNaI, *mptWorld, *mptMirror;
	
	G4int nCols, nRows;
	
	G4double xWorld, yWorld, zWorld, phi0, phi1, r0, r1, ir1, AlThick, barrelHeight, flangeThick, rOuter, sensDetHalfThick;
	
	const G4double HCMUM = 1.239841939*eV;
	const G4double HCNM = 1.239841939*keV;
	const G4double rhoAl = 2.710*g/cm3;
	//const G4double aAl=26.9815*g/mole;
	//const G4double macAl=0.02232*cm2/g;
	const G4double rhoNaI = 3.67*g/cm3;
	//const G4double mmNaI=149.89*g/mole;
	
	G4bool isPMT;
	
	G4GenericMessenger *fMessenger;
	
	G4LogicalVolume *fScoringVolume;
	
	void DefineMaterials();
	void ConstructHousing();
	void ConstructScintillator();
	void ConstructSensDet();
	
	virtual void ConstructSDandField();
};

#endif
