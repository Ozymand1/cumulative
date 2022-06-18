#include <G4VSensitiveDetector.hh>
//#include "DetectorConstruction.hh"
#include "G4RootAnalysisManager.hh"
#include "TupleId.hh"
class TTree;

class SensetiveDetector : public G4VSensitiveDetector{
public:
    explicit SensetiveDetector(std::string name, TupleId* tupleId) : G4VSensitiveDetector(name), tupleId(tupleId){

    };
    G4bool ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist) override;

    ~SensetiveDetector() override;

    void Initialize(G4HCofThisEvent *event) override;

    void EndOfEvent(G4HCofThisEvent *event) override;

private:
    TupleId* tupleId;
};