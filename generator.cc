#include "generator.hh"
MyPrimaryGenerator::MyPrimaryGenerator(){
    if(MyDetectorConstruction::scintillatorArrangement=="SC"){
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

    } else if(MyDetectorConstruction::scintillatorArrangement=="SCBT"|| MyDetectorConstruction::scintillatorArrangement == "RPCBT"){


    particleSource = new G4GeneralParticleSource(); 
    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    
    G4ParticleDefinition *particle = particleTable->FindParticle(13);//13 corresponds to a muon in Geant4 database
    
    //The particle is generated in the origin with direction z+ and energy of 1 GeV
   // G4ThreeVector pos(0.,0.,0.);
    //G4ThreeVector mom(0.,0.,1.);
    //particleSource->SetParticlePosition(pos);
    //particleSource->SetParticleMomentumDirection(mom);
   // particleSource->GetCurrentSource()->GetEneDist()->SetMonoEnergy(1.*GeV);
    //particleSource->SetParticleDefinition(particle);
     //G4int numberOfParticles = 2000;
   // particleSource->SetMultipleParticleFlag(true);
    //particleSource->SetNumberOfParticles(numberOfParticles);
    
    }
}
MyPrimaryGenerator::~MyPrimaryGenerator(){
if(MyDetectorConstruction::scintillatorArrangement=="SC"){
    delete fParticleGun;
}
if(MyDetectorConstruction::scintillatorArrangement=="SCBT" || MyDetectorConstruction::scintillatorArrangement == "RPCBT"){
    delete particleSource;
}
}
void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent){
    if(MyDetectorConstruction::scintillatorArrangement=="SC")
    {
        fParticleGun->GeneratePrimaryVertex(anEvent);
    }
    if(MyDetectorConstruction::scintillatorArrangement=="SCBT" || MyDetectorConstruction::scintillatorArrangement == "RPCBT")
    {
        particleSource->GeneratePrimaryVertex(anEvent);
    }
}

    
