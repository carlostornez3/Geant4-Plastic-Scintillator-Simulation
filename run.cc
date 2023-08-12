#include "run.hh"
#include "construction.hh"
#include "G4UIcommand.hh"


 //Creation of histograms
 //#include "G4RootAnalysisManager.hh"
MyRunAction::MyRunAction(){
   G4AnalysisManager *man =G4AnalysisManager::Instance();
  
   man->CreateH1("fEdep","Energy Deposition by Muons",60,0.,12*MeV,"MeV");
   man->SetH1XAxisTitle(0,"Energy Deposition (MeV)");
   man->SetH1YAxisTitle(0,"Number of Muons");

   man->CreateH1("fWlength","Photon Wavelength",60,360*nm,525*nm,"nm");
   man->SetH1XAxisTitle(1,"Wavelength (nm)");
   man->SetH1YAxisTitle(1,"Number of Photons");
   
   man->CreateH1("fEvent","Amount of Photons produced per event",30,0,1000,"none");
   man->SetH1XAxisTitle(2,"Event");
   man->SetH1YAxisTitle(2,"Number of Photons");

   
   man->CreateH1("fEnergy","Photon Energy",80,2.*eV,4.*eV,"eV");
   man->SetH1XAxisTitle(3,"Energy (eV)");
   man->SetH1YAxisTitle(3,"Number of Photons");

   man->CreateH1("fEvent2","Amount of Photons produced per event",10,0,10,"none");
   man->SetH1XAxisTitle(4,"Event");
   man->SetH1YAxisTitle(4,"Number of Photons");

   man->CreateH1("fTime0","Time of flight Event 0",150,0.*ns,70.*ns,"ns");
   man->SetH1XAxisTitle(5,"Time of flight (ns)");
   man->SetH1YAxisTitle(5,"Number of Photons");

    man->CreateH1("fTime1","Time of flight Event 1",150,0.*ns,70.*ns,"ns");
   man->SetH1XAxisTitle(6,"Time of flight (ns)");
   man->SetH1YAxisTitle(6,"Number of Photons");
   
   man->CreateH1("fTime2","Time of flight Event 2",150,0.*ns,70.*ns,"ns");
   man->SetH1XAxisTitle(7,"Time of flight (ns)");
   man->SetH1YAxisTitle(7,"Number of Photons");

   man->CreateH1("fTime3","Time of flight Event 3",150,0.*ns,70.*ns,"ns");
   man->SetH1XAxisTitle(8,"Time of flight (ns)");
   man->SetH1YAxisTitle(8,"Number of Photons");

   man->CreateH1("fTime4","Time of flight Event 4",150,0.*ns,70.*ns,"ns");
   man->SetH1XAxisTitle(9,"Time of flight (ns)");
   man->SetH1YAxisTitle(9,"Number of Photons");

   man->CreateH1("fTime5","Time of flight Event 5",150,0.*ns,70.*ns,"ns");
   man->SetH1XAxisTitle(10,"Time of flight (ns)");
   man->SetH1YAxisTitle(10,"Number of Photons");

   man->CreateH1("fTime6","Time of flight Event 6",150,0.*ns,70.*ns,"ns");
   man->SetH1XAxisTitle(11,"Time of flight (ns)");
   man->SetH1YAxisTitle(11,"Number of Photons");

   man->CreateH1("fTime7","Time of flight Event 7",150,0.*ns,70.*ns,"ns");
   man->SetH1XAxisTitle(12,"Time of flight (ns)");
   man->SetH1YAxisTitle(12,"Number of Photons");

   man->CreateH1("fTime8","Time of flight Event 8",150,0.*ns,70.*ns,"ns");
   man->SetH1XAxisTitle(13,"Time of flight (ns)");
   man->SetH1YAxisTitle(13,"Number of Photons");

   man->CreateH1("fTime9","Time of flight Event 9",150,0.*ns,70.*ns,"ns");
   man->SetH1XAxisTitle(14,"Time of flight (ns)");
   man->SetH1YAxisTitle(14,"Number of Photons");
    
   man->CreateH1("fTime10","Time of flight ",150,0.*ns,100000*ns,"ns");
   man->SetH1XAxisTitle(15,"Time of flight (ns)");
   man->SetH1YAxisTitle(15,"Number of Photons");
   man->SetH1Activation(15, false);

   man->CreateH1("MTOF","Mean Time of flight",60,0*ns,12*ns,"ns");
   man->SetH1XAxisTitle(16,"Time of flight (ns)");
   //man->SetH1YAxisTitle(16,"Number of Photons");

   man->CreateH1("fEvent4","Amount of Photons produced",1000,0,100000,"none");
   man->SetH1YAxisTitle(17,"Event");
   man->SetH1XAxisTitle(17,"Number of Photons");
   man->SetH1Activation(17, false);

   man->CreateH1("fEvent3","Amount of Photons produced",150,0,15000,"none");
   man->SetH1YAxisTitle(18,"Events");
   man->SetH1XAxisTitle(18,"Number of Photons");

  /*  man->CreateH1("fEvent5","Amount of Photons produced",1000,0,100000,"none");
   man->SetH1YAxisTitle(19,"Event");
   man->SetH1XAxisTitle(19,"Number of Photons");
   //man->SetH1Activation(19, false);*/


   man->CreateH2("fEnergy vs fWlength","Photon Energy vs Photon Wavelength",80,2.4*eV,3.5*eV,60,300*nm,520*nm,"eV","nm");
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
   // G4String thickness = G4UIcommand::ConvertToString(MyDetectorConstruction::scintillatorThickness); strRunID.str()
    G4String file =MyDetectorConstruction::scintillatorGeometry+"_"+ MyDetectorConstruction::scintillatorType +"_" + G4UIcommand::ConvertToString(MyDetectorConstruction::scintillatorThickness) + "mm"  + ".root";
  
    man->OpenFile(file);


}
void MyRunAction::EndOfRunAction(const G4Run *){
    G4AnalysisManager *man =G4AnalysisManager::Instance();
    man->Write();
    man->CloseFile();
}
