
//ROOT
#include "TTree.h"
#include "TLorentzVector.h"

//Geant
#include "G4Event.hh"

//local classes
#include "MCEvent.h"
#include "DetUtils.h"

//_____________________________________________________________________________
MCEvent::MCEvent(): Detector(), fNam("MCEvent") {

  ClearEvent();

}//MCEvent

//_____________________________________________________________________________
void MCEvent::BeginEvent(const G4Event *evt) {

  G4PrimaryVertex *pvtx = evt->GetPrimaryVertex();
  if(!pvtx) return;

  //position of generated vertex, mm
  fVx = pvtx->GetX0();
  fVy = pvtx->GetY0();
  fVz = pvtx->GetZ0();

  //G4cout << "MCEvent::BeginEvent: " << fVx << " " << fVy << " " << fVz << G4endl;

  //particles loop
  for(G4int i=0; i<pvtx->GetNumberOfParticle(); i++) {
    G4PrimaryParticle *part = pvtx->GetPrimary(i);

    //read the photon and electron
    G4int pdg = part->GetPDGcode();
    if(pdg == 22) ReadPhoton(part);
    if(pdg == 11) ReadElectron(part);

  }//particles loop

}//BeginEvent

//_____________________________________________________________________________
void MCEvent::ReadPhoton(G4PrimaryParticle *part) {

  //generated photon variables

  //G4cout << "MCEvent::ReadPhoton: " << part->GetPDGcode() << G4endl;

  //energy of generated gamma photon
  fPhotGen = part->GetTotalEnergy();
  fPhotGen = fPhotGen/1.0e3; // to GeV

  //azimuthal and polar angle
  GetThetaPhi(part, fPhotTheta, fPhotPhi);

}//ReadPhoton

//_____________________________________________________________________________
void MCEvent::ReadElectron(G4PrimaryParticle *part) {

  //scattered electron

  //G4cout << "MCEvent::ReadElectron: " << part->GetPDGcode() << G4endl;

  //electron energy
  fElGen = part->GetTotalEnergy();
  fElGen = fElGen/1.0e3; // to GeV

  //G4cout << "MCEvent::ReadElectron: " << fElGen << G4endl;

  //electron azimuthal and polar angle
  GetThetaPhi(part, fElTheta, fElPhi);

}//ReadElectron

//_____________________________________________________________________________
void MCEvent::GetThetaPhi(G4PrimaryParticle *part, Double_t &theta, Double_t &phi) {

  //theta and phi angles for generated particle

  //energy and momentum for Lorentz vector
  G4double en = part->GetTotalEnergy()/1.0e3; // to GeV
  G4double px = part->GetPx()/1.0e3;
  G4double py = part->GetPy()/1.0e3;
  G4double pz = part->GetPz()/1.0e3;

  //Lorentz vector for angles
  TLorentzVector vec;
  vec.SetPxPyPzE(px, py, pz, en);

  //azimuthal and polar angle
  theta = vec.Theta();
  phi = vec.Phi();

}//GetThetaPhi

//_____________________________________________________________________________
void MCEvent::CreateOutput(TTree *tree) {

  //set MC output branches

  DetUtils u("", tree);

  u.AddBranch("pXsec", &fpXsec, "D");
  u.AddBranch("uXsec", &fuXsec, "D");

  u.AddBranch("phot_en", &fPhotGen, "D");
  u.AddBranch("phot_theta", &fPhotTheta, "D");
  u.AddBranch("phot_phi", &fPhotPhi, "D");

  u.AddBranch("vtx_x", &fVx, "D");
  u.AddBranch("vtx_y", &fVy, "D");
  u.AddBranch("vtx_z", &fVz, "D");

  u.AddBranch("el_gen", &fElGen, "D");
  u.AddBranch("el_theta", &fElTheta, "D");
  u.AddBranch("el_phi", &fElPhi, "D");

}//CreateOutput

//_____________________________________________________________________________
void MCEvent::ClearEvent() {

  // fpXsec = 0.;//for whatever reason we clear the event at the beginning of the event so if you uncomment these the values are lost
  // fuXsec = 0.;
  fPhotGen = 0.;
  fPhotTheta = 0.;
  fPhotPhi = 0.;

  fVx = -9999.;
  fVy = -9999.;
  fVz = -9999.;

  fElGen = 0.;
  fElTheta = 0.;
  fElPhi = 0.;

}//ClearEvent











