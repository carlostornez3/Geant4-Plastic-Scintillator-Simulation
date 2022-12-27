#include "generator.hh"
MyPrimaryGenerator::MyPrimaryGenerator(){
fParticleGun = new G4ParticleGun(1); //En paréntesis va el número de partículas generadas por evento
    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition *particle = particleTable->FindParticle(13);

    G4ThreeVector pos(0.,0.,0.);
    G4ThreeVector mom(0.,0.,1.);
    fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleMomentumDirection(mom);
    fParticleGun->SetParticleEnergy(4.*GeV);
    fParticleGun->SetParticleDefinition(particle);
}
MyPrimaryGenerator::~MyPrimaryGenerator(){
delete fParticleGun;
}
void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent){


    fParticleGun->GeneratePrimaryVertex(anEvent);
}