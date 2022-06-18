#include <G4UserRunAction.hh>
#include "G4Run.hh"
#include "TupleId.hh"

class RunAction : public G4UserRunAction{
public:
    explicit RunAction(TupleId* tupleId);
    void BeginOfRunAction(const G4Run* aRun) override;
    void EndOfRunAction(const G4Run* aRun) override;

private:
    TupleId* tupleId;
};