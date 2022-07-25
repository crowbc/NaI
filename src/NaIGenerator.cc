#include "NaIGenerator.hh"

NaIPrimaryGenerator::NaIPrimaryGenerator()
{
	fParticleGun = new G4ParticleGun(1);
	
	G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
	G4String particleName = "geantino";	
	G4ParticleDefinition *particle = particleTable->FindParticle(particleName);
	
	G4ThreeVector pos(6.7675*cm,0.,1.*cm);
	G4ThreeVector mom(0.,0.,1.);
	
	fParticleGun->SetParticlePosition(pos);
	fParticleGun->SetParticleMomentumDirection(mom);
	fParticleGun->SetParticleMomentum(0.*MeV);
	fParticleGun->SetParticleDefinition(particle);
}

NaIPrimaryGenerator::~NaIPrimaryGenerator()
{
	delete fParticleGun;
}

void NaIPrimaryGenerator::GeneratePrimaries(G4Event *NaIEvent)
{
	G4ParticleDefinition *particle = fParticleGun->GetParticleDefinition();
	// default to Co-60 decay if particle is defined as geantino	
	if(particle==G4Geantino::Geantino())
	{
		G4int Z = 27;
		G4int A = 60;
		
		G4double charge = 0.*eplus;
		G4double energy = 0.*keV;
		
		G4ParticleDefinition *ion = G4IonTable::GetIonTable()->GetIon(Z, A, energy);
		
		fParticleGun->SetParticleDefinition(ion);
		fParticleGun->SetParticleCharge(charge);
	}
	
	fParticleGun->GeneratePrimaryVertex(NaIEvent);
}
