#include "DetectorConstruction.hh"
#include <G4NistManager.hh>
#include <G4Box.hh>
#include <G4PVPlacement.hh>
#include <G4SDManager.hh>
#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"
#include <G4Tubs.hh>
#include <G4Cons.hh>

//#include "CylindricalSD.hh"


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
    CreatePIDdetector(logicWorld);
    CreateEnergyDetector(logicWorld);
    CreateTrackingDetector(logicWorld);
    CreateDummy(logicWorld);
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

G4VPhysicalVolume* DetectorConstruction::CreatePIDdetector(G4LogicalVolume *world_logic) {
    auto PID_solid = new G4Tubs("PID_solid",
                                   0.5 * PID_inner_diameter,
                                   0.5 *  PID_diameter,
                                   0.5 * PID_lenght,
                                   0,
                                   2 * pi);
    auto PID_logic = new G4LogicalVolume(PID_solid,
                                            PID_mat,
                                            "PID_logic");
    auto PID_phys = new G4PVPlacement(0,
                                        PID_position,
                                         PID_logic,
                                         "PID_detector",
                                         world_logic,
                                         false,
                                         0);
    G4cout<<PID_position/cm<<G4endl;
    return PID_phys;
}

G4VPhysicalVolume* DetectorConstruction::CreateEnergyDetector(G4LogicalVolume *world_logic) {
    auto Energy_solid = new G4Tubs("Energy_solid",
                                0.5 * Energy_inner_diameter,
                                0.5 *  Energy_diameter,
                                0.5 * Energy_lenght,
                                0,
                                2 * pi);
    auto Energy_logic = new G4LogicalVolume(Energy_solid,
                                            Energy_mat,
                                         "Energy_logic");
    auto Energy_phys = new G4PVPlacement(0,
                                         Energy_position,
                                         Energy_logic,
                                      "Energy_detector",
                                      world_logic,
                                      false,
                                      0);

    return Energy_phys;
}

G4VPhysicalVolume* DetectorConstruction::CreateTrackingDetector(G4LogicalVolume *world_logic) {
    double rmin1 = Track_distance_from_target * tan(theta_1) - 1.0*cm;
    double rmax1 = Track_distance_from_target * tan(theta_2) + 1.0*cm;
    double rmin2 = (Track_distance_from_target + Track_lenght) * tan(theta_2) - 1.0*cm;
    double rmax2 = (Track_distance_from_target + Track_lenght) * tan(theta_2) + 1.0*cm;
    auto Track_solid = new G4Cons("Track_solid",
                                  0.5*rmin2,
                                  0.5*rmax2,
                                  0.5*rmin1,
                                  0.5*rmax1,
                                  0.5*Track_lenght,
                                  0,
                                  2*pi);
    auto Track_logic = new G4LogicalVolume(Track_solid,
                                           vacuum,
                                            "Track_logic");
    auto Track_phys = new G4PVPlacement(0,
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
        auto x = Track_position.x();
        auto y = Track_position.y();
        auto z =  - i * (Track_lenght * parts - 0.5 * layer_width) + 0.5 * Track_lenght;
        G4ThreeVector position = G4ThreeVector(x,y,z);
        z = -1 * Track_distance_from_target - 0.5 * layer_width- i * (Track_lenght * parts - 0.5 * layer_width);
        Layer_logic[i] = CreateTrackingLayer(abs(z), i);
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

G4LogicalVolume* DetectorConstruction::CreateTrackingLayer(G4double distance_from_target, int number) {
    G4double Track_inner_diameter = (distance_from_target + 1 * Track_distance_from_target + 0.5 * layer_width-0.5*Track_lenght) * tan(theta_1);
    G4double Track_outer_diameter = (distance_from_target + 1 * Track_distance_from_target + 0.5 * layer_width-0.5*Track_lenght) * tan(theta_2);
    std::string  solid_name = "Layer_solid_" + to_string(number);
    std::string  logic_name = "Layer_logic_" + to_string(number);
    auto Layer_solid = new G4Tubs(solid_name,
                                  0.5 * Track_inner_diameter,
                                  0.5 * Track_outer_diameter,
                                  0.5 * layer_width,
                                  0,
                                  2 * pi);
    auto Layer_logic = new G4LogicalVolume(Layer_solid,
                                           Track_mat,
                                           logic_name);
    return Layer_logic;

}

G4VPhysicalVolume* DetectorConstruction::CreateDummy(G4LogicalVolume *world_logic) {
    auto Dummy_solid =
            new G4Box("Dummy_solid",
                      0.5 * Dummy_width,
                      0.5 * Dummy_height,
                      0.5 * Dummy_lenght);

    auto Dummy_logic =
            new G4LogicalVolume(Dummy_solid,
                                Dummy_mat,
                                "Dummy_logic");

    auto Dummy_phys =
            new G4PVPlacement(0,
                              Dummy_position,
                              Dummy_logic,
                              "Dummy",
                              logicWorld,
                              false,
                              0);

    return Dummy_phys;
}

void DetectorConstruction::InitializeMaterials() {
    auto nist = G4NistManager::Instance();
    vacuum = nist->FindOrBuildMaterial("G4_Galactic");
    target_mat = nist->FindOrBuildMaterial(target_material);
    PID_mat = nist->FindOrBuildMaterial(PID_material);
    Energy_mat = nist->FindOrBuildMaterial(Energy_material);
    Track_mat = nist->FindOrBuildMaterial(Track_material);
    Dummy_mat = nist->FindOrBuildMaterial(Dummy_material);
}


/*void DetectorConstruction::ConstructSDandField() {
    G4VUserDetectorConstruction::ConstructSDandField();
    auto SDmanager = G4SDManager::GetSDMpointer();
    auto cylindricalSD = new CylindricalSD("Cylinder", tupleId);
    SDmanager->AddNewDetector(cylindricalSD);

cylinder_with_hole_logic->SetSensitiveDetector(cylindricalSD);
    cylinder_logic->SetSensitiveDetector(cylindricalSD);*

    logicWorld->SetSensitiveDetector(cylindricalSD);
}*/

