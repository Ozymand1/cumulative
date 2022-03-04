#include "RunAction.hh"
#include "G4AnalysisManager.hh"
// "g4analysis.hh"

void RunAction::BeginOfRunAction(const G4Run *aRun) {
    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->SetDefaultFileType("root");
    /*G4AnalysisManager *analysisManager = G4Analysis::ManagerInstance("root");
    analysisManager->OpenFile("500MeVRunData");
    tupleId->analysisManager = analysisManager;

    int FortyFiveId = analysisManager->CreateNtuple("FortyFive", "0.5 Run data");
    analysisManager->CreateNtupleDColumn("A" + std::to_string(45));
    analysisManager->FinishNtuple(FortyFiveId);
    //tupleId->FortyFiveId = FortyFiveId;

    int NinetyId = analysisManager->CreateNtuple("Ninety", "0.5 Run data");
    analysisManager->CreateNtupleDColumn("A" + std::to_string(90));
    analysisManager->FinishNtuple(NinetyId);
    //tupleId->NinetyId = NinetyId;

    int HundredThirtyFiveId = analysisManager->CreateNtuple("HundredAndFive", "0.5 Run data");
    analysisManager->CreateNtupleDColumn("A" + std::to_string(135));
    analysisManager->FinishNtuple(HundredThirtyFiveId);
    //tupleId->HundredThirtyFiveId = HundredThirtyFiveId;*/
}

void RunAction::EndOfRunAction(const G4Run *aRun) {
    /*G4UserRunAction::EndOfRunAction(aRun);
    G4AnalysisManager* analysisManager = G4Analysis::ManagerInstance("root");
    analysisManager->Write();
    analysisManager->CloseFile(true);*/
}

RunAction::RunAction(TupleId *tupleId) : tupleId(tupleId) {

}