#include "SensetiveDetector.hh"
using namespace CLHEP;

G4bool SensetiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist) {
    //if (aStep->GetTrack()->GetParticleDefinition()->GetPDGEncoding() == 2212 and
    //    aStep->GetTrack()->GetParentID() == 0){
    if (aStep->GetTrack()->GetParticleDefinition()->GetPDGEncoding() == 211 and
        aStep->GetTrack()->GetParentID() == 0){
        G4cout<<aStep->GetTrack()->GetVolume()->GetCopyNo()<<G4endl;
        reg_event this_event;
        this_event.mom = aStep->GetPreStepPoint()->GetMomentum().mag()/GeV;
        int copy_det = aStep->GetTrack()->GetVolume()->GetCopyNo();
        this_event.pos[0] = aStep->GetPreStepPoint()->GetPosition().x()/cm;
        this_event.pos[1] = aStep->GetPreStepPoint()->GetPosition().y()/cm;
        this_event.pos[2] = aStep->GetPreStepPoint()->GetPosition().z()/cm;
        this_event.tof = aStep->GetPreStepPoint()->GetGlobalTime()/nanosecond;
        this_event.det = aStep->GetPreStepPoint()->GetPhysicalVolume()->GetCopyNo();
        this_event.number = event_number;
        events.push_back(this_event);
        if (copy_det == 5){aStep->GetTrack()->SetTrackStatus(fStopAndKill);}
    }

    return 0;
}

SensetiveDetector::~SensetiveDetector() = default;

void SensetiveDetector::Initialize(G4HCofThisEvent *event) {
    G4VSensitiveDetector::Initialize(event);
    events.clear();
    event_number++;
}

void SensetiveDetector::EndOfEvent(G4HCofThisEvent *event) {
    G4VSensitiveDetector::EndOfEvent(event);

    G4cout<<"Detector name: "<<det_name<<G4endl;
    G4cout<<"Writing Data"<<G4endl;
    G4cout<<"number of hits = "<<events.size()<<G4endl;

    auto analysisManager = tupleId->analysisManager;

    bool Track[3] = {false, false, false};
    bool TOF = false;
    bool Energy = false;

    for (auto i: events) {
        for (int j = 1; j < 6; j++) {
            if(i.det == j and j < 4){
                Track[j-1] = true;
            }
            if(i.det == j and j == 4){
                TOF = true;
            }
            if(i.det == j and j == 5){
                Energy = true;
            }
        }

    }
    if ((Track[0] and Track[1] and Track[2]) or TOF or Energy){
        for (auto i: events) {
            analysisManager->FillNtupleDColumn(tupleId->hitsId, 0, i.pos[0]);
            analysisManager->FillNtupleDColumn(tupleId->hitsId, 1, i.pos[1]);
            analysisManager->FillNtupleDColumn(tupleId->hitsId, 2, i.pos[2]);
            analysisManager->FillNtupleDColumn(tupleId->hitsId, 3, i.mom);
            analysisManager->FillNtupleDColumn(tupleId->hitsId, 4, i.tof);
            analysisManager->FillNtupleDColumn(tupleId->hitsId, 5, i.det);
            analysisManager->FillNtupleDColumn(tupleId->hitsId, 6, i.number);
            analysisManager->AddNtupleRow(tupleId->hitsId);
            G4cout<<"x = "<<i.pos[0]<<G4endl;
            G4cout<<"y = "<<i.pos[1]<<G4endl;
            G4cout<<"z = "<<i.pos[2]<<G4endl;
            G4cout<<"momentum = "<<i.mom<<G4endl;
            G4cout<<"tof = "<<i.tof<<G4endl;
            G4cout<<"det = "<<i.det<<G4endl;
            G4cout<<"event_number = "<<i.number<<G4endl;
            G4cout<<" "<<G4endl;
        }
    }
    Track[0] = false;
    Track[1] = false;
    Track[2] = false;
    TOF = false;
    Energy = false;

}