#include "run.hh"
 //Creation of histograms
 
MyRunAction::MyRunAction(){
    G4AnalysisManager *man =G4AnalysisManager::Instance();
  
   man->CreateH1("fEdep","Energy Deposition by Muons",30,0.,12*MeV,"MeV");
   man->SetH1XAxisTitle(0,"Energy Deposition (MeV)");
   man->SetH1YAxisTitle(0,"Number of Muons");

   man->CreateH1("fWlength","Photon Wavelength",30,350,520,"nm");
   man->SetH1XAxisTitle(1,"Wavelength (nm)");
   man->SetH1YAxisTitle(1,"Number of Photons");
   
   man->CreateH1("fEvent","Amount of Photons produced per event",30,0,1000,"none");
   man->SetH1XAxisTitle(2,"Event");
   man->SetH1YAxisTitle(2,"Number of Photons");
   
   man->CreateH1("fEnergy","Photon Energy",30,2.4,3.5);
   man->SetH1XAxisTitle(3,"Energy (eV)");
   man->SetH1YAxisTitle(3,"Number of Photons");

   man->CreateH2("fEnergy vs fWlength","Photon Energy vs Photon Wavelength",30,2.4,3.5,30,350,520);
   man->SetH2XAxisTitle(0,"Photon Energy (eV)");
   man->SetH2YAxisTitle(0,"Photon Wavelength (nm)");
   man->SetH2ZAxisTitle(0,"Number of Photons");
}
MyRunAction::~MyRunAction(){

}
void MyRunAction::BeginOfRunAction(const G4Run * run){
    G4AnalysisManager *man =G4AnalysisManager::Instance();

    G4int runID = run->GetRunID();
    std::stringstream strRunID;
    strRunID<<runID;

    G4String file="output"+strRunID.str()+".root";
    man->OpenFile(file);
    


}
void MyRunAction::EndOfRunAction(const G4Run *){
    G4AnalysisManager *man =G4AnalysisManager::Instance();
    man->Write();
    man->CloseFile();
}