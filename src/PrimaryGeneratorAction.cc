#include <G4DynamicParticle.hh>
#include "PrimaryGeneratorAction.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "TRandom.h"
#include <random>

using namespace CLHEP;

void PrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent) {
    std::random_device rd;
    std::uniform_int_distribution<long> uid(0, LONG_MAX);
    long seed = uid(rd);
    fParticleGun->SetParticlePosition(G4ThreeVector(0, 0, 0));
    auto random = new TRandom;
    random->SetSeed(seed);
    for (int i = 0; i < 1 ; ++i) {
        random->TRandom::Sphere(x, y, z, 1);
        fParticleGun->SetParticleMomentumDirection(G4ThreeVector(x, y, z));
        fParticleGun->SetParticleEnergy(500 * MeV);
        fParticleGun->GeneratePrimaryVertex(anEvent);
    }

}

PrimaryGeneratorAction::PrimaryGeneratorAction() {
    G4int n_particle = 1;
    fParticleGun = new G4ParticleGun(n_particle);
}