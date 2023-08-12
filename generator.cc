#include "generator.hh"
MyPrimaryGenerator::MyPrimaryGenerator(){
    
    fParticleGun = new G4ParticleGun(1); //One particle per event
    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    
    G4ParticleDefinition *particle = particleTable->FindParticle(13);//13 corresponds to a muon in Geant4 database
    
    //The particle is generated in the origin with direction z+ and energy of 1 GeV
    G4ThreeVector pos(0.,0.,0.);
    G4ThreeVector mom(0.,0.,1.);
    fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleMomentumDirection(mom);
    fParticleGun->SetParticleMomentum(1.*GeV);
    fParticleGun->SetParticleDefinition(particle);
}
MyPrimaryGenerator::~MyPrimaryGenerator(){
delete fParticleGun;
}
void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent){


    fParticleGun->GeneratePrimaryVertex(anEvent);
}