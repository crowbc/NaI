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

#include "NaIDetectorConstruction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NaIDetectorConstruction::NaIDetectorConstruction()
{
	fMessenger = new G4GenericMessenger(this, "/detector/", "Detector Construction");
	
	fMessenger->DeclareProperty("xWorld", xWorld, "World volume x-dimension half-length");
	fMessenger->DeclareProperty("yWorld", yWorld, "World volume y-dimension half-length");
	fMessenger->DeclareProperty("zWorld", zWorld, "World volume z-dimension half-length");
	fMessenger->DeclareProperty("isPMT", isPMT, "Toggle sensitive detector geometry for PMT");
	
	xWorld = 0.5*m;
	yWorld = 0.5*m;
	zWorld = 0.5*m;
	
	isPMT = true;// set to false unless scintillation is simulated
	
	DefineMaterials();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NaIDetectorConstruction::~NaIDetectorConstruction()
{
	
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NaIDetectorConstruction::DefineMaterials()
{
	G4NistManager *nist = G4NistManager::Instance();
	
	size_t nI = 26;
	G4double energy[nI] = {HCMUM/0.8891, HCMUM/0.8451, HCMUM/0.8033, HCMUM/0.7636, HCMUM/0.7258, HCMUM/0.6899, HCMUM/0.6557, HCMUM/0.6233, HCMUM/0.5924, HCMUM/0.5631, 
		HCMUM/0.5353, HCMUM/0.5088, HCMUM/0.4836, HCMUM/0.4597, HCMUM/0.4369, HCMUM/0.4153, HCMUM/0.3947, HCMUM/0.3752, HCMUM/0.3566, HCMUM/0.339, 
		HCMUM/0.3222, HCMUM/0.3063, HCMUM/0.2911, HCMUM/0.2767, HCMUM/0.263, HCMUM/0.250};
	G4double rindexNaI[nI] = {1.7514793193028, 1.753338714921, 1.7554083069968, 1.7577134899302, 1.7602905913854, 1.7631680461798, 1.7663952687813, 1.7699994775469, 1.7740579536442, 1.7786098175401, 
		1.7837261117122, 1.7895164922257, 1.7960715386354, 1.8034913859982, 1.8119664988198, 1.8216138123297, 1.8327134075919, 1.8454461194368, 1.860241610754, 1.8774002096741, 
		1.8976189984837, 1.921442035403, 1.9500895751993, 1.984659056014, 2.0271744581354, 2.0803044182369};
	//G4double rindexAl[26] = {1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 
		//1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 
		//1.5, 1.5, 1.5, 1.5, 1.5, 1.5};
	G4double rindexWorld[nI] = {1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 
		1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 
		1., 1., 1., 1., 1., 1.};
	G4double absLengthNaI[nI] = {10.*cm, 10.*cm, 10.*cm, 10.*cm, 10.*cm, 10.*cm, 10.*cm, 10.*cm, 10.*cm, 10.*cm, 
		10.*cm, 10.*cm, 10.*cm, 10.*cm, 10.*cm, 10.*cm, 10.*cm, 10.*cm, 10.*cm, 10.*cm, 
		10.*cm, 10.*cm, 10.*cm, 10.*cm, 10.*cm, 10.*cm};// find believable values
	G4double absLengthAl[nI] = {10.*cm, 10.*cm, 10.*cm, 10.*cm, 10.*cm, 10.*cm, 10.*cm, 10.*cm, 10.*cm, 10.*cm, 
		10.*cm, 10.*cm, 10.*cm, 10.*cm, 10.*cm, 10.*cm, 10.*cm, 10.*cm, 10.*cm, 10.*cm, 
		10.*cm, 10.*cm, 10.*cm, 10.*cm, 10.*cm, 10.*cm};
	G4double fcNaI[nI] = {1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 
		1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 
		1., 1., 1., 1., 1., 1.};
	G4double scintYieldNaI = 38./keV;
	G4double ftcNaI = 250.*ns;
	G4double reflectivity[nI] = {1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 
		1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 
		1., 1., 1., 1., 1., 1.};
	
	wMat = nist->FindOrBuildMaterial("G4_AIR");
	
	Al = nist->FindOrBuildElement("Al");
	AlMat = new G4Material("AlMat", rhoAl, 1);
	AlMat->AddElement(Al, 1);
	
	NaI = new G4Material("NaI", rhoNaI, 2);
	Na = nist->FindOrBuildElement("Na");
	I = nist->FindOrBuildElement("I");
	NaI->AddElement(Na, 1);
	NaI->AddElement(I, 1);
	
	mptAl = new G4MaterialPropertiesTable();
	//mptAl->AddProperty("RINDEX", energy, rindexAl, 26);
	mptAl->AddProperty("ABSLENGTH", energy, absLengthAl, 26);
	AlMat->SetMaterialPropertiesTable(mptAl);
	
	mptNaI = new G4MaterialPropertiesTable();
	mptNaI->AddProperty("RINDEX", energy, rindexNaI, nI);
	mptNaI->AddProperty("ABSLENGTH", energy, absLengthNaI, nI);
	mptNaI->AddProperty("FASTCOMPONENT", energy, fcNaI, nI, true);
	mptNaI->AddConstProperty("SCINTILLATIONYIELD", scintYieldNaI);
	mptNaI->AddConstProperty("RESOLUTIONSCALE", 1.0, true);
	mptNaI->AddConstProperty("FASTTIMECONSTANT", ftcNaI, true);
	mptNaI->AddConstProperty("YIELDRATIO", 1.0, true);
	NaI->SetMaterialPropertiesTable(mptNaI);
	
	mptWorld = new G4MaterialPropertiesTable();
	mptWorld->AddProperty("RINDEX", energy, rindexWorld, nI);
	wMat->SetMaterialPropertiesTable(mptWorld);
	
	mirrorSurface = new G4OpticalSurface("mirrorSurface");
	mirrorSurface->SetType(dielectric_metal);
	mirrorSurface->SetFinish(ground);
	mirrorSurface->SetModel(unified);
	
	mptMirror = new G4MaterialPropertiesTable();
	mptMirror->AddProperty("REFLECTIVITY", energy, reflectivity, nI);
	mirrorSurface->SetMaterialPropertiesTable(mptMirror);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NaIDetectorConstruction::ConstructHousing()
{
	phi0 = 0.*deg;
	phi1 = 360.*deg;
	r0 = 0.*mm;
	r1 = (5.25*25.4/2)*mm;
	ir1=2.5*25.4*mm;
	AlThick = r1-ir1;
	barrelHeight = 4.75*25.4*mm-AlThick;
	flangeThick = 0.75*25.4*mm;
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
	logicBottom = new G4LogicalVolume(bottom, AlMat, "logicBottom");
	logicBarrel = new G4LogicalVolume(barrel, AlMat, "logicBarrel");
	logicFlange = new G4LogicalVolume(flange, AlMat, "logicFlange");
	
	skinBottom = new G4LogicalSkinSurface("skinBottom", logicBottom, mirrorSurface);
	skinBarrel = new G4LogicalSkinSurface("skinBarrel", logicBarrel, mirrorSurface);
	
	// physical volumes for detector components
	physBottom = new G4PVPlacement(0, G4ThreeVector(0.,0.,z0), logicBottom, "physBottom", logicWorld, false, 0, true);
	physBarrel = new G4PVPlacement(0, G4ThreeVector(0.,0.,z1), logicBarrel, "physBarrel", logicWorld, false, 0, true);
	physFlange = new G4PVPlacement(0, G4ThreeVector(0.,0.,z3), logicFlange, "physFlange", logicWorld, false, 0, true);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NaIDetectorConstruction::ConstructScintillator()
{
	phi0 = 0.*deg;
	phi1 = 360.*deg;
	r0 = 0.*mm;
	r1 = (5.25*25.4/2)*mm;
	ir1=2.5*25.4*mm;
	AlThick = r1-ir1;
	barrelHeight = 4.75*25.4*mm-AlThick;
	flangeThick = 0.75*25.4*mm;
	// Declare placement variable
	G4double z2=AlThick+barrelHeight/2+flangeThick/2;
	G4double zCrys=z2-AlThick;
	
	crystal = new G4Tubs("crystal", r0, ir1, zCrys, phi0, phi1);
	
	logicCrystal = new G4LogicalVolume(crystal, NaI, "logicCrystal");
	
	physCrystal = new G4PVPlacement(0, G4ThreeVector(0.,0.,z2), logicCrystal, "physCrystal", logicWorld, false, 0, true);
	
	fScoringVolume=logicCrystal;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NaIDetectorConstruction::ConstructSensDet()
{
	phi0 = 0.*deg;
	phi1 = 360.*deg;
	r0 = 0.*mm;
	r1 = (5.25*25.4/2)*mm;
	ir1=2.5*25.4*mm;
	AlThick = r1-ir1;
	barrelHeight = 4.75*25.4*mm-AlThick;
	flangeThick = 0.75*25.4*mm;
	sensDetHalfThick = 10.00*mm;
	// Deckare placement variable
	G4double z4=AlThick+barrelHeight+flangeThick+sensDetHalfThick;
	
	solidDetector = new G4Tubs("solidDetector", r0, ir1, sensDetHalfThick, phi0, phi1);
	
	logicDetector = new G4LogicalVolume(solidDetector, wMat, "logicDetector");
	
	physDetector = new G4PVPlacement(0, G4ThreeVector(0.,0.,z4), logicDetector, "physDetector", logicWorld, false, 0, true);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

G4VPhysicalVolume* NaIDetectorConstruction::Construct()
{	
	wBox = new G4Box("wBox", xWorld, yWorld, zWorld);
	
	logicWorld =  new G4LogicalVolume(wBox, wMat, "logicWorld");
	
	physWorld = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicWorld, "physWorld", 0, false, 0, true);
	
	ConstructHousing();
	
	ConstructScintillator();
	
	if(isPMT)
	{
		ConstructSensDet();
	}
	
	return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NaIDetectorConstruction::ConstructSDandField()
{
	NaISensitiveDetector *sensDet = new NaISensitiveDetector("PMT");
	if(isPMT)
	{
		logicDetector->SetSensitiveDetector(sensDet);
	}
}
