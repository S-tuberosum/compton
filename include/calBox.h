
#ifndef calBox_h
#define calBox_h

// simple calorimeter, V2

#include "Detector.h"
#include "G4VSensitiveDetector.hh"

class G4GenericMessenger;
class G4VPhysicalVolume;
class G4Step;

class calBox : public Detector, public G4VSensitiveDetector {

  public:

    calBox(const G4String&, G4double x, G4double y, G4double z,G4double rot, G4double xysize,G4double zsize,G4LogicalVolume *top);
    virtual ~calBox() {}

    //called via G4VSensitiveDetector
    virtual G4bool ProcessHits(G4Step *step, G4TouchableHistory*);

    //called via Detector
    virtual const G4String& GetName() const {return fNam;}
    virtual void CreateOutput(TTree *tree);
    virtual void ClearEvent();

  private:

    G4GenericMessenger *fMsg; // messenger for detectors and components
    G4String fNam; // detector name

    Bool_t fSelectPrim; // flag to select only primary track in ProcessHits

    Bool_t fIsHit; // hit by primary particle
    Double_t fEnPrim; // energy of the primary particle
    Double_t fEnAll; // sum of energy of all particles in event

    Double_t fHx; // hit position in x
    Double_t fHy; // hit position in y
    Double_t fHz; // hit position in z
    G4double resMean = 1; G4double resSD = 0; // energy resolution mean and standard deviation (default is perfect resolution)


/*
    G4VPhysicalVolume *fSens; //detector sensitive volume
    OpDet *fOpDet; // optical detector attached to the crystal

    void AddBranch(const std::string& nam, Double_t *val, TTree *tree);
    void AddBranch(const std::string& nam, ULong64_t *val, TTree *tree);

    Double_t fEdep; // deposited energy in the detector
    Double_t fX; // x of first point in the detector
    Double_t fY; // y of first point
    Double_t fZ; // z of first point

    ULong64_t fNphot; // number of optical photons
    ULong64_t fNscin; // scintillation photons
    ULong64_t fNcerenkov; // Cerenkov photons

    G4int fScinType; // scintillation process type
    G4int fScinSubType; // scintillation process subtype
    G4int fCerenkovType; // Cerenkov process type
    G4int fCerenkovSubType; // Cerenkov process subtype
*/
};

#endif



















