#include <DetectorConstruction.hh>
#include <PrimaryGeneratorAction.hh>
#include <QGSP_BERT.hh>
#include <G4VisManager.hh>
#include <G4VisExecutive.hh>
#include <G4UIExecutive.hh>
#include <G4UImanager.hh>
#include <RunAction.hh>
#include <random>
#include "G4RunManager.hh"

using namespace CLHEP;

int main(int argc, char **argv) {
    std::random_device rd;
    std::uniform_int_distribution<long> uid(0, LONG_MAX);
    long seed = uid(rd);
    HepRandom::setTheSeed(seed);
    std::cout<<"Seed "<<seed<<std::endl;
    G4UIExecutive *ui = nullptr;
    std::cout<<argc<<" "<<argv[0]<<std::endl;
    if(argc == 1) {
        ui = new G4UIExecutive(argc, argv);
    }
    TupleId *tupleId = new TupleId();
    auto runManager = new G4RunManager;
    runManager->SetUserInitialization(new DetectorConstruction(tupleId));
    runManager->SetUserInitialization(new QGSP_BERT());
    runManager->SetUserAction(new PrimaryGeneratorAction());
    runManager->SetUserAction(new RunAction(tupleId));
    runManager->Initialize();

    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialise();

    auto UImanager = G4UImanager::GetUIpointer();

    if(!ui) {
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command + fileName);
    } else {
        UImanager->ApplyCommand("/control/execute init_vis.mac");
        ui->SessionStart();
        delete ui;
    }
    delete visManager;
    delete runManager;
}
