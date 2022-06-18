#include "G4SystemOfUnits.hh"
using namespace CLHEP;

const G4double theta_1 = 120.0 * deg;
const G4double theta_2 = 160.0 * deg;
const G4double deltaTheta = theta_2 - theta_1;

const G4String target_material = "G4_W";
const G4ThreeVector target_position = G4ThreeVector(0 * cm,0 * cm, 0 * cm);
const G4double target_lenght = 0.5 * cm;
const G4double target_diameter = 10 * cm;

const G4String TOF_stop_material = "G4_Si";
const G4ThreeVector TOF_stop_position = G4ThreeVector(0 * cm,180 * tan(pi- theta_2 + deltaTheta / 2) * cm,-180 * cm);
const G4double TOF_stop_lenght = 0.2 * cm;
const G4double TOF_stop_size = 50 * cm;

const G4String Energy_material = "G4_Pb";
const G4ThreeVector Energy_position = G4ThreeVector(0 * cm,200 * tan(pi- theta_2 + deltaTheta / 2) * cm, -200 * cm);
const G4double Energy_lenght = 20 * cm;
const G4double Energy_width = 50 * cm;
const G4double Energy_height = 30 * cm;

const G4String Track_material = "G4_Si";
const G4double Track_size = 3 * cm;
const G4double Track_lenght = 3 * cm;
const G4double Track_distance_from_target = 10.0 * cm;
const G4ThreeVector Track_position = G4ThreeVector(0.0 * cm,(0.5 * Track_lenght + Track_distance_from_target) * tan(pi- theta_2 + deltaTheta / 2), -(0.5 * Track_lenght + Track_distance_from_target));
const int Number_of_tracking_layers = 3;
const G4double layer_width = 0.10 * cm;
