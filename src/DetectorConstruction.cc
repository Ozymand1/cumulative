#include "DetectorConstruction.hh"
#include <G4NistManager.hh>
#include <G4Box.hh>
#include <G4PVPlacement.hh>
#include <G4SDManager.hh>
#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"
#include <G4Tubs.hh>
#include "SensetiveDetector.hh"
G4double CalculateSize(G4double position){

    G4double size = position * tan(deltaTheta / 2) / cos((pi - theta_2  + deltaTheta / 2));

    return size;
}
G4VPhysicalVolume* DetectorConstruction::Construct() {
    G4bool checkOverlaps = true;

    G4double world_sizeXY = 10 * meter;
    G4double world_sizeZ = 10 * meter;

    auto solidWorld =
            new G4Box("World",
                      0.5 * world_sizeXY,
                      0.5 * world_sizeXY,
                      0.5 * world_sizeZ);

    logicWorld =
            new G4LogicalVolume(solidWorld,
                                vacuum,
                                "World");

    auto physWorld =
            new G4PVPlacement(0,
                              G4ThreeVector(0*cm, 0*cm, 0*cm),
                              logicWorld,
                              "World",
                              0,
                              false,
                              0,
                              checkOverlaps);
    CreateTarget(logicWorld);
    CreateTOFstopDetector(logicWorld);
    CreateEnergyDetector(logicWorld);
    CreateTrackingDetector(logicWorld);
    return physWorld;
}

G4VPhysicalVolume* DetectorConstruction::CreateTarget(G4LogicalVolume *world_logic) {
    auto target_solid = new G4Tubs("target_solid",
                               0,
                               0.5 *  target_diameter,
                               0.5 * target_lenght,
                               0,
                               2 * pi);
    auto target_logic = new G4LogicalVolume(target_solid,
                                        target_mat,
                                        "target_logic");
    auto target_phys = new G4PVPlacement(0,
                                     target_position,
                                     target_logic,
                                     "target",
                                     world_logic,
                                     false,
                                     0);

    return target_phys;
}

G4VPhysicalVolume* DetectorConstruction::CreateEnergyDetector(G4LogicalVolume *world_logic) {
    G4double size = abs(CalculateSize(abs(Energy_position.z()/cm)));
    G4cout<<CalculateSize(abs(Energy_position.z())/cm)<<G4endl;
    G4cout<<theta_1<<" "<<cos((pi - theta_2  + deltaTheta / 2))<<" "<<tan(deltaTheta/2)<<G4endl;
    auto Energy_solid = new G4Box("Energy_solid", size, size, 15 * cm);
    auto Energy_logic = new G4LogicalVolume(Energy_solid,
                                            Energy_mat,
                                            "Energy_logic");


    auto Rotation_Matrix = new G4RotationMatrix();
    Rotation_Matrix->rotateX(- (pi - theta_2 + deltaTheta / 2));
    auto Energy_phys = new G4PVPlacement(Rotation_Matrix,
                                         Energy_position,
                                         Energy_logic,
                                         "Energy_detector",
                                         world_logic,
                                         false,
                                         0);

    return Energy_phys;
}

G4VPhysicalVolume* DetectorConstruction::CreateTrackingDetector(G4LogicalVolume *world_logic) {
    auto Rotation_Matrix = new G4RotationMatrix();
    Rotation_Matrix->rotateX(- (pi - theta_2 + deltaTheta / 2));
    auto Track_solid = new G4Box("Tracking_solid", Track_size, Track_size, Track_lenght);
    auto Track_logic = new G4LogicalVolume(Track_solid,
                                           vacuum,
                                           "Track_logic");
    auto Track_phys = new G4PVPlacement(Rotation_Matrix,
                                        Track_position,
                                        Track_logic,
                                        "Tracking_detector",
                                        world_logic,
                                        false,
                                        0);
    std::cout<<Track_position.z()/cm<<std::endl;
    G4LogicalVolume* Layer_logic[Number_of_tracking_layers];
    G4double parts = 1.0/(Number_of_tracking_layers-1);
    for (int i = 0; i < Number_of_tracking_layers; i++) {
        auto x = 0;
        auto y = 0;
        auto z =  - i * (Track_lenght * parts - 0.5 * layer_width) + 0.5 * Track_lenght;
        G4ThreeVector position = G4ThreeVector(x,y,z);
        z = -1 * Track_distance_from_target - 0.5 * layer_width- i * (Track_lenght * parts - 0.5 * layer_width);
        Layer_logic[i] = CreateTrackingLayer(i);
        std::cout<<z/cm<<std::endl;
        auto Layer_phys = new G4PVPlacement(0,
                                            position,
                                            Layer_logic[i],
                                            "Tracking_Layer",
                                            Track_logic,
                                            false,
                                            0);
    }
    return Track_phys;
}

G4LogicalVolume* DetectorConstruction::CreateTrackingLayer(int number) {
    std::string  solid_name = "Layer_solid_" + to_string(number);
    std::string  logic_name = "Layer_logic_" + to_string(number);
    auto Layer_solid = new G4Box(solid_name, Track_size, Track_size, layer_width);
    auto Layer_logic = new G4LogicalVolume(Layer_solid,
                                           Track_mat,
                                           logic_name);
    return Layer_logic;
}

G4VPhysicalVolume* DetectorConstruction::CreateTOFstopDetector(G4LogicalVolume *world_logic) {
    auto Rotation_Matrix = new G4RotationMatrix();
    Rotation_Matrix->rotateX(- (pi - theta_2 + deltaTheta / 2));
    auto TOF_solid = new G4Box("PID_solid", TOF_stop_size, TOF_stop_size, Track_lenght);
    auto TOF_logic = new G4LogicalVolume(TOF_solid, TOF_mat, "TOF_logic");
    auto TOF_phys = new G4PVPlacement(Rotation_Matrix,
                                      TOF_stop_position,
                                      TOF_logic,
                                      "PID_detector",
                                      world_logic,
                                      false,
                                      0);
    G4cout<<TOF_stop_position/cm<<G4endl;
    return TOF_phys;
}

void DetectorConstruction::InitializeMaterials() {
    auto nist = G4NistManager::Instance();
    vacuum = nist->FindOrBuildMaterial("G4_Galactic");
    target_mat = nist->FindOrBuildMaterial(target_material);
    TOF_mat = nist->FindOrBuildMaterial(TOF_stop_material);
    Energy_mat = nist->FindOrBuildMaterial(Energy_material);
    Track_mat = nist->FindOrBuildMaterial(Track_material);
}


void DetectorConstruction::ConstructSDandField() {
    G4VUserDetectorConstruction::ConstructSDandField();
    auto SDmanager = G4SDManager::GetSDMpointer();
    auto Detector = new SensetiveDetector("Detector", tupleId);
    SDmanager->AddNewDetector(Detector);
}

