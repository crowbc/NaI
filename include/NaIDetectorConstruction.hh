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
// start conditional to define class only once
#ifndef NAIDETECTORCONSTRUCTION_HH
#define NAIDETECTORCONSTRUCTION_HH
// included Geant4 header files
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
// included user defined header file
#include "NaIDetector.hh"
// create the class
class NaIDetectorConstruction : public G4VUserDetectorConstruction
{
public:
	NaIDetectorConstruction();
	~NaIDetectorConstruction();
	
	G4LogicalVolume *GetScoringVolume() const { return fScoringVolume; }
	
	virtual G4VPhysicalVolume* Construct();
	
private:
	// Declare solid, logical and physical volumes used in NaIDetectorConstruction.cc
	G4Box *wBox;
	G4Tubs *solidDetector, *bottom, *barrel, *flange, *crystal;
	G4LogicalVolume *logicWorld, *logicDetector, *logicBottom, *logicBarrel, *logicFlange, *logicCrystal;
	G4VPhysicalVolume *physWorld, *physDetector, *physBottom, *physBarrel, *physFlange, *physCrystal;
	// Declare optical surfaces
	G4OpticalSurface *mirrorSurface;
	G4LogicalSkinSurface *skinBarrel, *skinBottom;
	// Declare materials and properties tables
	G4Material *air, *aluminium, *NaI;
	G4Element *Na, *I;
	G4MaterialPropertiesTable *mptAl, *mptNaI, *mptWorld, *mptMirror;
	// Declare variables used in constructor and in defining volumes	
	G4double xWorld, yWorld, zWorld, phi0, phi1, r0, r1, ir1, AlThick, barrelHeight, flangeThick, rOuter, sensDetHalfThick;
	G4bool isPMT;
	// conversion factor
	const G4double in = 25.4*mm;
	// physical constants
	const G4double HCMUM = 1.239841939*eV;
	const G4double HCNM = 1239.841939*eV;
	// specified densities
	const G4double rhoAl = 2.710*g/cm3;
	const G4double rhoNaI = 3.67*g/cm3;
	// constants for dispersion coefficients and factors
	const G4double a0NaI = 1.478;
	const G4double a1NaI = 1.532;
	const G4double b1NaI = 0.170;
	const G4double a2NaI = 4.27;
	const G4double b2NaI = 86.21;
	// constants for NaI scintillation properties
	const G4double scintYieldNaI = 40000./MeV;// see ref (1)
	const G4double stcNaI = 230.*ns;// see ref(1) & ref(2)
	// From Hamamatsu Catalog (values in microns:)
	const G4double meanWlenNaI = 0.410;
	const G4double FWHMNaI = 0.110;
	// constants for wavelength calculations (wavelengths given in microns)
	const G4double wlenMax = 0.9000;
	const G4double wlenMin = 0.2000;
	// Declare Messenger for setting parameters	
	G4GenericMessenger *fMessenger;
	// Declare scoring volume
	G4LogicalVolume *fScoringVolume;
	// declare functions
	void DefineMaterials();
	void ConstructHousing();
	void ConstructScintillator();
	void ConstructSensDet();
	virtual void ConstructSDandField();
};
// end of conditional to ensure class is defined only once
#endif
