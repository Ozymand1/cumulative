#include <G4DynamicParticle.hh>
#include "PrimaryGeneratorAction.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "G4Proton.hh"
#include "G4PionPlus.hh"
#include "TRandom.h"
#include <random>

using namespace CLHEP;

void PrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent) {
    //fParticleGun->SetParticleDefinition(G4Proton::Definition());
    fParticleGun->SetParticleDefinition(G4PionPlus::Definition());
    fParticleGun->SetParticlePosition(G4ThreeVector(0, 0, 0));
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0, 0.64278761, -0.766044443));
    fParticleGun->SetParticleMomentum(1 * GeV);
    fParticleGun->GeneratePrimaryVertex(anEvent);
}

PrimaryGeneratorAction::PrimaryGeneratorAction() {
    G4int n_particle = 1;
    fParticleGun = new G4ParticleGun(n_particle);
}