#include "G4SystemOfUnits.hh"
using namespace CLHEP;

const G4String target_material = "G4_W";
const G4ThreeVector target_position = G4ThreeVector(0 * cm,0 * cm, 25 * cm);
const double target_lenght = 50 * cm;
const double target_diameter = 10 * cm;


const G4String PID_material = "G4_Si";
const G4ThreeVector PID_position = G4ThreeVector(0 * cm,0 * cm, -25 * cm);
const double PID_lenght = 2 * cm;
const double PID_diameter = 50 * cm;
const double PID_inner_diameter = 30 * cm;

const G4String Energy_material = "G4_Si";
const G4ThreeVector Energy_position = G4ThreeVector(0 * cm,0 * cm, -50 * cm);
const double Energy_lenght = 2 * cm;
const double Energy_diameter = 50 * cm;
const double Energy_inner_diameter = 30 * cm;

const G4String Track_material = "G4_Si";
const G4ThreeVector Track_position = G4ThreeVector(0 * cm,0 * cm, -37.5 * cm);
const double Track_lenght = 3 * cm;
const double Track_diameter = 50 * cm;
const double Track_inner_diameter = 40 * cm;
const int Number_of_tracking_layers = 3;
const int Number_of_segments = 36;
const double layer_width = 0.20 * cm;

const G4String Dummy_material = "G4_Pb";
const G4ThreeVector Dummy_position = G4ThreeVector(0 * cm,0 * cm, 80 * cm);
const double Dummy_lenght = 50 * cm;
const double Dummy_width = 20 * cm;
const double Dummy_height = 20 * cm;