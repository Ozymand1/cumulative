#include <G4VUserDetectorConstruction.hh>
#include "G4LogicalVolume.hh"
#include "GeometrySize.hh"
#include "G4SystemOfUnits.hh"
#include "TupleId.hh"

using namespace CLHEP;

class DetectorConstruction : public G4VUserDetectorConstruction{
public:

    G4VPhysicalVolume* Construct() override;

    void ConstructSDandField() override;
    G4VPhysicalVolume* CreateTOFstopDetector(G4LogicalVolume* world_logic);
    G4VPhysicalVolume* CreateTrackingDetector(G4LogicalVolume* world_logic);
    G4VPhysicalVolume* CreateEnergyDetector(G4LogicalVolume* world_logic);
    G4VPhysicalVolume* CreateTarget(G4LogicalVolume* world_logic);
    G4LogicalVolume* CreateTrackingLayer(int number);
    explicit DetectorConstruction(TupleId* tupleId) : tupleId(tupleId){
        InitializeMaterials();
    }
private:
    G4Material* vacuum;
    G4Material* target_mat;
    G4Material* TOF_mat;
    G4Material* Energy_mat;
    G4Material* Track_mat;
    G4LogicalVolume* CreateDetector();
    G4LogicalVolume* logicWorld;
    TupleId* tupleId;
    void InitializeMaterials();
};