#include <G4VUserDetectorConstruction.hh>
#include "G4LogicalVolume.hh"
#include "GeometrySize.hh"
#include "G4SystemOfUnits.hh"
#include "TupleId.hh"
using namespace CLHEP;

class DetectorConstruction : public G4VUserDetectorConstruction{
public:

    G4VPhysicalVolume* Construct() override;

    //void ConstructSDandField() override;
    G4VPhysicalVolume* CreatePIDdetector(G4LogicalVolume* world_logic);
    G4VPhysicalVolume* CreateTrackingDetector(G4LogicalVolume* world_logic);
    G4VPhysicalVolume* CreateEnergyDetector(G4LogicalVolume* world_logic);
    G4VPhysicalVolume* CreateTarget(G4LogicalVolume* world_logic);
    G4VPhysicalVolume* CreateDummy(G4LogicalVolume* world_logic);
    G4LogicalVolume* CreateTrackingLayer(G4double distance_from_target, int number);
    explicit DetectorConstruction(TupleId* tupleId) : tupleId(tupleId){
        InitializeMaterials();
    }
private:
    G4Material* vacuum;
    G4Material* target_mat;
    G4Material* PID_mat;
    G4Material* Energy_mat;
    G4Material* Track_mat;
    G4Material* Dummy_mat;
    G4LogicalVolume* CreateDetector();
    G4LogicalVolume* detector_logic;
    G4LogicalVolume* cylinder_logic;
    G4LogicalVolume* detector_logical;
    G4LogicalVolume* cylinder_with_hole_logic;
    G4LogicalVolume* logicWorld;
    TupleId* tupleId;
    void InitializeMaterials();
};