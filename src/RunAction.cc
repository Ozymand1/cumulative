#include "RunAction.hh"
#include "G4AnalysisManager.hh"
#include "G4RootAnalysisManager.hh"

void RunAction::BeginOfRunAction(const G4Run *aRun) {
    auto analysisManager = G4RootAnalysisManager::Instance();
    analysisManager->OpenFile("Test");
    tupleId->analysisManager = analysisManager;
    G4cout<<"Creating Ntuple"<<G4endl;
    int hits = analysisManager->CreateNtuple("hits", "test runs data");
    analysisManager->CreateNtupleDColumn("x");
    analysisManager->CreateNtupleDColumn("y");
    analysisManager->CreateNtupleDColumn("z");
    analysisManager->CreateNtupleDColumn("mom");
    analysisManager->CreateNtupleDColumn("tof");
    analysisManager->CreateNtupleDColumn("det");
    analysisManager->CreateNtupleDColumn("number");
    analysisManager->FinishNtuple(hits);
    analysisManager->FillNtupleDColumn(hits, 2);
    tupleId->hitsId = hits;

}

void RunAction::EndOfRunAction(const G4Run *aRun) {
    G4cout<<"Finishing Run"<<G4endl;
    G4UserRunAction::EndOfRunAction(aRun);
    auto analysisManager = G4RootAnalysisManager::Instance();
    analysisManager->Write();
    analysisManager->CloseFile(true);
}

RunAction::RunAction(TupleId *tupleId) : tupleId(tupleId) {

}