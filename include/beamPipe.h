#ifndef beamPipe_h
#define beamPipe_h

// beam pipe

#include "Detector.h"
#include "G4VSensitiveDetector.hh"

class beamPipe : public Detector, public G4VSensitiveDetector {

  public:
    beamPipe(G4String nam, G4double xpos,G4double ypos,G4double zpos,G4double length, G4double r1, G4double r2, G4double dout, G4double angle, G4LogicalVolume*);
    virtual ~beamPipe() {}

    //Detector
    virtual const G4String& GetName() const {return fNam;}

    //G4VSensitiveDetector
    virtual G4bool ProcessHits(G4Step *, G4TouchableHistory*);

  private:

    G4String fNam; // beamPipe name

};

#endif