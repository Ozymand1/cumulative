#ifndef TUPLEID_HH
#define TUPLEID_HH
#include "G4RootAnalysisManager.hh"

struct TupleId{
    G4RootAnalysisManager* analysisManager;
    int hitsId = -1;
};
#endif