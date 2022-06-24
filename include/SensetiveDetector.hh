#include <G4VSensitiveDetector.hh>
//#include "DetectorConstruction.hh"
#include "G4RootAnalysisManager.hh"
#include "TupleId.hh"
class TTree;

class SensetiveDetector : public G4VSensitiveDetector{
public:
    explicit SensetiveDetector(std::string name, TupleId* tupleId) : G4VSensitiveDetector(name), tupleId(tupleId){
        det_name = name;
    };
    G4bool ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist) override;

    ~SensetiveDetector() override;

    void Initialize(G4HCofThisEvent *event) override;

    void EndOfEvent(G4HCofThisEvent *event) override;

private:
    std::string det_name;
    TupleId* tupleId;
    struct reg_event{
        double pos[3] = {0,0,0};
        double mom = 0;
        double tof = 0;
        int det = 0;
        int number = 0;
    };
    std::vector<reg_event> events;
    int event_number = 0;
};