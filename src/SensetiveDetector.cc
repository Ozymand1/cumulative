#include "SensitiveDetector.hh"
using namespace CLHEP;

G4bool SensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist) {
        energy = aStep->GetPostStepPoint()->GetKineticEnergy();

    return 0;
}

SensitiveDetector::~CylindricalSD() = default;

void SensitiveDetector::Initialize(G4HCofThisEvent *event) {
    G4VSensitiveDetector::Initialize(event);
    energy = 0;
    for (int & i : angular) {
        i = 0;

    }
}

void SensitiveDetector::EndOfEvent(G4HCofThisEvent *event) {
    G4VSensitiveDetector::EndOfEvent(event);


    auto analysisManager = tupleId->analysisManager;

    if (angular[0] == 1){
        analysisManager->FillNtupleDColumn(tupleId->FortyFiveId, 0, energy);
        analysisManager->AddNtupleRow(tupleId->FortyFiveId);
    }

    if (angular[1] == 1){
        analysisManager->FillNtupleDColumn(tupleId->NinetyId, 0, energy);
        analysisManager->AddNtupleRow(tupleId->NinetyId);
    }

    if (angular[2] == 1){
        analysisManager->FillNtupleDColumn(tupleId->HundredThirtyFiveId, 0, energy);
        analysisManager->AddNtupleRow(tupleId->HundredThirtyFiveId);
    }

}