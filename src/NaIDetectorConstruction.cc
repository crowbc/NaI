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
/// \file NaIDetectorConstruction.cc
/// \brief Implementation of the NaIDetectorConstruction class
// included user defined header file
#include "NaIDetectorConstruction.hh"
// Constructor
NaIDetectorConstruction::NaIDetectorConstruction()
{
	fMessenger = new G4GenericMessenger(this, "/detector/", "Detector Construction");
	fMessenger->DeclareProperty("xWorld", xWorld, "World volume x-dimension half-length");
	fMessenger->DeclareProperty("yWorld", yWorld, "World volume y-dimension half-length");
	fMessenger->DeclareProperty("zWorld", zWorld, "World volume z-dimension half-length");
	fMessenger->DeclareProperty("isPMT", isPMT, "Toggle sensitive detector geometry for PMT");
	// set default values
	xWorld = 0.5*m;
	yWorld = 0.5*m;
	zWorld = 0.5*m;
	// toggle sensitive geometry
	isPMT = true;
	// Call Material Definintion function in constructor
	DefineMaterials();
}
// Destructor
NaIDetectorConstruction::~NaIDetectorConstruction()
{}
// Define detector materials and set properties
void NaIDetectorConstruction::DefineMaterials()
{
	G4NistManager *nist = G4NistManager::Instance();
	// Declare variables for material properties. Define constant for derived quantity
	size_t nI = 141;
	G4double wlenMUM[nI];
	G4double energy[nI];
	G4double rindexNaI[nI];
	G4double rindexAir[nI];
	G4double absLengthNaI[nI];
	G4double absLengthAl[nI];
	G4double scNaI[nI];
	G4double reflAl[nI];
	// wavelength increment size in microns
	const G4double wlenDelta = (wlenMax-wlenMin)/(nI-1);
	// for loop for defining material properties
	for(size_t i = 0; i<nI; i++){
		// Set wavlengths from 0.900 micron to 0.200 micron in steps of 0.005 micron (when nI = 141)
		wlenMUM[i] = wlenMax-i*wlenDelta;
		energy[i] = HCMUM/wlenMUM[i];
		// see ref(3) for source of refractive index formula
		rindexNaI[i] = sqrt(a0NaI+a1NaI*wlenMUM[i]*wlenMUM[i]/(wlenMUM[i]*wlenMUM[i]-b1NaI*b1NaI)+a2NaI*wlenMUM[i]*wlenMUM[i]/(wlenMUM[i]*wlenMUM[i]-b2NaI*b2NaI));
		absLengthNaI[i] = 2.59*cm;// see ref(1) & (2)
		scNaI[i] = exp(-2*(wlenMUM[i]-meanWlenNaI)*(wlenMUM[i]-meanWlenNaI)/(FWHMNaI*FWHMNaI));
		rindexAir[i] = 1.;
		reflAl[i] = 0.95;// TODO: search literature & find believable values
		// Debug message - disable to reduce run time
		//G4cout << "wavelength (microns:) " << wlenMUM[i] << "; energy (eV:) " << energy[i]*1E06 << "; refractive index: " << rindexNaI[i] << G4endl;
	}
	// define materials starting with air
	air = nist->FindOrBuildMaterial("G4_AIR");
	aluminium = nist->FindOrBuildMaterial("G4_Al");
	// TODO: define NaI from Nist Manager
	NaI = new G4Material("NaI", rhoNaI, 2);
	Na = nist->FindOrBuildElement("Na");
	I = nist->FindOrBuildElement("I");
	NaI->AddElement(Na, 1);
	NaI->AddElement(I, 1);
	// set aluminum properties
	mptAl = new G4MaterialPropertiesTable();
	mptAl->AddProperty("REFLECTIVITY", energy, reflAl, nI);
	aluminium->SetMaterialPropertiesTable(mptAl);
	// set NaI properties
	mptNaI = new G4MaterialPropertiesTable();
	mptNaI->AddProperty("RINDEX", energy, rindexNaI, nI);
	mptNaI->AddProperty("ABSLENGTH", energy, absLengthNaI, nI);
	mptNaI->AddProperty("SCINTILLATIONCOMPONENT1", energy, scNaI, nI);
	mptNaI->AddConstProperty("SCINTILLATIONYIELD", scintYieldNaI);
	mptNaI->AddConstProperty("RESOLUTIONSCALE", 1.0);
	mptNaI->AddConstProperty("SCINTILLATIONTIMECONSTANT1", stcNaI);
	mptNaI->AddConstProperty("SCINTILLATIONYIELD1", 1.0);
	NaI->SetMaterialPropertiesTable(mptNaI);
	// set air properties
	mptWorld = new G4MaterialPropertiesTable();
	mptWorld->AddProperty("RINDEX", energy, rindexAir, nI);
	air->SetMaterialPropertiesTable(mptWorld);
	// optical surface properties
	mirrorSurface = new G4OpticalSurface("mirrorSurface");
	mirrorSurface->SetType(dielectric_metal);
	mirrorSurface->SetFinish(ground);
	mirrorSurface->SetModel(unified);
	mirrorSurface->SetMaterialPropertiesTable(mptAl);
}
// Construct aluminum housing components
void NaIDetectorConstruction::ConstructHousing()
{
	phi0 = 0.*deg;
	phi1 = 360.*deg;
	r0 = 0.*mm;
	r1 = 5.25*in/2;
	ir1 = 2.5*in;
	AlThick = r1-ir1;
	barrelHeight = 4.75*in-AlThick;
	flangeThick = 0.75*in;
	rOuter = r1+16.5*mm;
	sensDetHalfThick = 10.00*mm;
	// Declare placement variables
	G4double z0=AlThick/2;
	G4double z1=AlThick+barrelHeight/2;
	G4double z3=AlThick+barrelHeight+flangeThick/2;
	// define shapes for detector housing and PMT sensitive region
	bottom = new G4Tubs("bottom", r0, r1, AlThick/2, phi0, phi1);
	barrel = new G4Tubs("barrel", ir1, r1, barrelHeight/2, phi0, phi1);
	flange = new G4Tubs("flange", ir1, rOuter, flangeThick/2, phi0, phi1);
	// logical volumes for housing components
	logicBottom = new G4LogicalVolume(bottom, aluminium, "logicBottom");
	logicBarrel = new G4LogicalVolume(barrel, aluminium, "logicBarrel");
	logicFlange = new G4LogicalVolume(flange, aluminium, "logicFlange");
	// define logical surfaces
	skinBottom = new G4LogicalSkinSurface("skinBottom", logicBottom, mirrorSurface);
	skinBarrel = new G4LogicalSkinSurface("skinBarrel", logicBarrel, mirrorSurface);
	// physical volumes for detector components
	physBottom = new G4PVPlacement(0, G4ThreeVector(0.,0.,z0), logicBottom, "physBottom", logicWorld, false, 0, true);
	physBarrel = new G4PVPlacement(0, G4ThreeVector(0.,0.,z1), logicBarrel, "physBarrel", logicWorld, false, 0, true);
	physFlange = new G4PVPlacement(0, G4ThreeVector(0.,0.,z3), logicFlange, "physFlange", logicWorld, false, 0, true);
}
// Construct scintillator volume
void NaIDetectorConstruction::ConstructScintillator()
{
	phi0 = 0.*deg;
	phi1 = 360.*deg;
	r0 = 0.*mm;
	r1 = 5.25*in/2;
	ir1 = 2.5*in;
	AlThick = r1-ir1;
	barrelHeight = 4.75*in-AlThick;
	flangeThick = 0.75*in;
	// Declare placement variable
	G4double z2=AlThick+barrelHeight/2+flangeThick/2;
	G4double zCrys=z2-AlThick;
	// Define solid, logical and physical volumes
	crystal = new G4Tubs("crystal", r0, ir1, zCrys, phi0, phi1);
	logicCrystal = new G4LogicalVolume(crystal, NaI, "logicCrystal");
	physCrystal = new G4PVPlacement(0, G4ThreeVector(0.,0.,z2), logicCrystal, "physCrystal", logicWorld, false, 0, true);
	// set scintillator as scoring volume
	fScoringVolume=logicCrystal;
}
// Construct sensitive region
void NaIDetectorConstruction::ConstructSensDet()
{
	phi0 = 0.*deg;
	phi1 = 360.*deg;
	r0 = 0.*mm;
	r1 = 5.25*in/2;
	ir1 = 2.5*in;
	AlThick = r1-ir1;
	barrelHeight = 4.75*in-AlThick;
	flangeThick = 0.75*in;
	sensDetHalfThick = 10.00*mm;
	// Declare placement variable
	G4double z4=AlThick+barrelHeight+flangeThick+sensDetHalfThick;
	// Define solid, logical and physical volumes
	solidDetector = new G4Tubs("solidDetector", r0, ir1, sensDetHalfThick, phi0, phi1);
	logicDetector = new G4LogicalVolume(solidDetector, air, "logicDetector");
	physDetector = new G4PVPlacement(0, G4ThreeVector(0.,0.,z4), logicDetector, "physDetector", logicWorld, false, 0, true);
}
// Detector Construction Method
G4VPhysicalVolume* NaIDetectorConstruction::Construct()
{	
	// define solid, logical and physical mother volumes
	wBox = new G4Box("wBox", xWorld, yWorld, zWorld);
	logicWorld =  new G4LogicalVolume(wBox, air, "logicWorld");
	physWorld = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicWorld, "physWorld", 0, false, 0, true);
	// Construct daughter volumes
	ConstructHousing();
	ConstructScintillator();
	// construct sensitive volume if toggled on
	if(isPMT)
	{
		ConstructSensDet();
	}
	// return value
	return physWorld;
}
// Method for constructing and specifying sensitive detector
void NaIDetectorConstruction::ConstructSDandField()
{
	NaISensitiveDetector *sensDet = new NaISensitiveDetector("PMT");
	if(isPMT)
	{
		logicDetector->SetSensitiveDetector(sensDet);
	}
}
