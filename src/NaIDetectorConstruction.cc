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
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
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
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// Destructor
NaIDetectorConstruction::~NaIDetectorConstruction()
{}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// Define detector materials and set properties
void NaIDetectorConstruction::DefineMaterials()
{
	G4NistManager *nist = G4NistManager::Instance();
	// Declare variables for material properties. Define constants for known quantities
	size_t nI = 141;
	G4double wlenMUM[nI];
	G4double energy[nI];
	G4double rindexNaI[nI];
	G4double rindexWorld[nI];
	G4double absLengthNaI[nI];
	G4double absLengthAl[nI];
	G4double scNaI[nI];
	G4double reflectivity[nI];
	// constants for wavelength calculations (wavelengths given in microns)
	const G4double wlenMax = 0.9000;
	const G4double wlenMin = 0.2000;
	const G4double wlenDelta = (wlenMax-wlenMin)/(nI-1);
	// constants for dispersion coefficients and factors
	const G4double a0NaI = 1.478;
	const G4double a1NaI = 1.532;
	const G4double b1NaI = 0.170;
	const G4double a2NaI = 4.27;
	const G4double b2NaI = 86.21;
	/*
	More data on NaI:
	source:	IOP Publishing 1221 (2022) 012002
	DOI:		doi:10.1088/1757-899X/1221/1/012002
	_____________________________________________________________________________________________________________________________________________________________________________
	Scintillation crystal	Elemental composition (wt.%)	Light yield (photons/MeV)	Decay time, τ (ns)	Radiation length (cm)	Density (g/cm 3 )	Ref.(s)
	_____________________________________________________________________________________________________________________________________________________________________________
	PWO (PbWO4)		45.5%Pb; 40.5%W 14.0% O	250				5-15			0.89			8.28			[7, 14, 15]
	PbF2			84.5%Pb; 15.5%F		<1000				30, 6			0.93			7.77			[16, 17]
	CsI			51.1%Cs; 48.8%I		16,800				10			1.86			4.51			[17, 18]
	LYSO:Ce		57.5%Lu; 3.24%Y		30,000				40			1.14			7.11			[2, 5, 8, 15, 19]
	(0.05 mol.%)		24.63%Si; 14.6%O
				0.01% Ce
	LuAG:Ce		61.6%Lu; 15.8%Al		25,000				820, 50		1.45			6.76			[5, 20]
	(0.1 mol.%)		22.5%O; 0.02%Ce
	BaF 2 :Y		76.29%Ba; 21.1%F		2,000				600, 0.5		2.03			4.89			[5, 9]
	(5 mol.%)		2.6%Y
	BGO			67.1 %Bi; 17.5%Ge		8200				300			1.12			7.13			[18, 20]
	(Bi4Ge3O12)		15.4%O
	NaI:Tl			15.27%Na; 84.31%I		40,000				230			2.59			3.67			[1, 20]
	(0.3 mol.%)		0.41%Tl
	_____________________________________________________________________________________________________________________________________________________________________________
	References:
			[1] Blasse G, 1994, Scintillator materialsChem. Mater. 6 1465-1475.
			[20] HuC,LiJ,YangF,JiangB,ZhangL,andZhuR-Y, 2020, LuAG ceramic scintillators for future HEP experiments
				Nucl. Instrum. Methods Phys. Res. A 954 161723.
	*/
	// constants for scintillation properties
	const G4double scintYieldNaI = 40./keV;// see above table
	const G4double stcNaI = 230.*ns;// see above table
	// for loop for defining material properties
	for(size_t i = 0; i<nI; i++){
		// Set wavlengths from 0.900 micron to 0.200 micron in steps of 0.005micron (when nI = 141)
		wlenMUM[i] = wlenMax-i*wlenDelta;
		energy[i] = HCMUM/wlenMUM[i];
		/************************************************************************************************************/
		/* Reference for dispersion formula shown below: https://refractiveindex.info/?shelf=main&book=NaI&page=Li  */
		/* dispersion formula as function of wavelength: n^2−1=0.478+1.532*λ^2/(λ^2−0.170^2)+4.27*λ^2/(λ^2−86.21^2) */
		/* See also J. Phys. Chem. Ref. Data 5, 329-528 (1976) at https://aip.scitation.org/doi/10.1063/1.555536    */
		/************************************************************************************************************/
		rindexNaI[i] = sqrt(a0NaI+a1NaI*wlenMUM[i]*wlenMUM[i]/(wlenMUM[i]*wlenMUM[i]-b1NaI*b1NaI)+a2NaI*wlenMUM[i]*wlenMUM[i]/(wlenMUM[i]*wlenMUM[i]-b2NaI*b2NaI));
		absLengthNaI[i] = 2.59*cm;// see above table
		scNaI[i] = 1.;// search literature. find believable values
		rindexWorld[i] = 1.;
		//absLengthAl[i] = 10.*cm;// search literature. find believable values
		reflectivity[i] = 1.;// search literature. find believable values
		// Debug message - disable to reduce run time
		//G4cout << "wavelength (microns:) " << wlenMUM[i] << "; energy (eV:) " << energy[i]*1E06 << "; refractive index: " << rindexNaI[i] << G4endl;
	}
	// define materials starting with air
	wMat = nist->FindOrBuildMaterial("G4_AIR");
	// to do: define aluminum from Nist Manager
	Al = nist->FindOrBuildElement("Al");
	aluminium = new G4Material("aluminium", rhoAl, 1);
	aluminium->AddElement(Al, 1);
	// to do: define NaI from Nist Manager
	NaI = new G4Material("NaI", rhoNaI, 2);
	Na = nist->FindOrBuildElement("Na");
	I = nist->FindOrBuildElement("I");
	NaI->AddElement(Na, 1);
	NaI->AddElement(I, 1);
	// set aluminum properties
	mptAl = new G4MaterialPropertiesTable();
	//mptAl->AddProperty("ABSLENGTH", energy, absLengthAl, nI);
	mptAl->AddProperty("REFLECTIVITY", energy, reflectivity, nI);
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
	mptWorld->AddProperty("RINDEX", energy, rindexWorld, nI);
	wMat->SetMaterialPropertiesTable(mptWorld);
	// optical surface properties
	mirrorSurface = new G4OpticalSurface("mirrorSurface");
	mirrorSurface->SetType(dielectric_metal);
	mirrorSurface->SetFinish(ground);
	mirrorSurface->SetModel(unified);
	mirrorSurface->SetMaterialPropertiesTable(mptAl);
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// Construct aluminum housing components
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
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// Construct scintillator volume
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
	// Define solid, logical and physical volumes
	crystal = new G4Tubs("crystal", r0, ir1, zCrys, phi0, phi1);
	logicCrystal = new G4LogicalVolume(crystal, NaI, "logicCrystal");
	physCrystal = new G4PVPlacement(0, G4ThreeVector(0.,0.,z2), logicCrystal, "physCrystal", logicWorld, false, 0, true);
	// set scintillator as scoring volume
	fScoringVolume=logicCrystal;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// Construct sensitive region
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
	// Declare placement variable
	G4double z4=AlThick+barrelHeight+flangeThick+sensDetHalfThick;
	// Define solid, logical and physical volumes
	solidDetector = new G4Tubs("solidDetector", r0, ir1, sensDetHalfThick, phi0, phi1);
	logicDetector = new G4LogicalVolume(solidDetector, wMat, "logicDetector");
	physDetector = new G4PVPlacement(0, G4ThreeVector(0.,0.,z4), logicDetector, "physDetector", logicWorld, false, 0, true);
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
// Detector Construction Method
G4VPhysicalVolume* NaIDetectorConstruction::Construct()
{	
	// define solid, logical and physical mother volumes
	wBox = new G4Box("wBox", xWorld, yWorld, zWorld);
	logicWorld =  new G4LogicalVolume(wBox, wMat, "logicWorld");
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
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// Method for constructing and specifying sensitive detector
void NaIDetectorConstruction::ConstructSDandField()
{
	NaISensitiveDetector *sensDet = new NaISensitiveDetector("PMT");
	if(isPMT)
	{
		logicDetector->SetSensitiveDetector(sensDet);
	}
}
