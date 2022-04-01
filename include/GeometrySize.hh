#include "G4SystemOfUnits.hh"
using namespace CLHEP;

const G4String target_material = "G4_W";
const G4ThreeVector target_position = G4ThreeVector(0 * cm,0 * cm, 25 * cm);
const G4double target_lenght = 0.5 * cm;
const G4double target_diameter = 10 * cm;


const G4String PID_material = "G4_Si";
const G4ThreeVector PID_position = G4ThreeVector(0 * cm,0 * cm, -25 * cm);
const G4double PID_lenght = 2 * cm;
const G4double PID_diameter = 50 * cm;
const G4double PID_inner_diameter = 30 * cm;

const G4String TOF_start_material = "G4_Si";
const G4ThreeVector TOF_start_position = G4ThreeVector(0 * cm,0 * cm, -25 * cm);
const G4double TOF_start_lenght = 2 * cm;
const G4double TOF_start_diameter = 50 * cm;
const G4double TOF_start_inner_diameter = 30 * cm;

const G4String TOF_stop_material = "G4_Si";
const G4ThreeVector TOF_stop_position = G4ThreeVector(0 * cm,0 * cm, -25 * cm);
const G4double TOF_stop_lenght = 2 * cm;
const G4double TOF_stop_diameter = 50 * cm;
const G4double TOF_stop_inner_diameter = 30 * cm;

const G4String Energy_material = "G4_Si";
const G4ThreeVector Energy_position = G4ThreeVector(0 * cm,0 * cm, -50 * cm);
const G4double Energy_lenght = 2 * cm;
const G4double Energy_diameter = 50 * cm;
const G4double Energy_inner_diameter = 30 * cm;

const G4String Track_material = "G4_Si";
const G4double theta_2 = (180-120.0)/180.0*pi*rad;
const G4double theta_1 = (180-130.0)/180.0*pi*rad;
const G4double Track_lenght = 3 * cm;
const G4double Track_distance_from_target = 10.0 * cm;
const G4ThreeVector Track_position = G4ThreeVector(0.0 * cm,0.0 * cm, -(0.5 * Track_lenght + Track_distance_from_target));
const int Number_of_tracking_layers = 4;
const int Number_of_segments = 36;
const G4double layer_width = 0.10 * cm;

const G4String Dummy_material = "G4_Pb";
const G4ThreeVector Dummy_position = G4ThreeVector(0 * cm,0 * cm, 80 * cm);
const G4double Dummy_lenght = 50 * cm;
const G4double Dummy_width = 20 * cm;
const G4double Dummy_height = 20 * cm;