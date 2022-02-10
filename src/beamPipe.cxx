//_____________________________________________________________________________
//
// Beam pipe
//
//_____________________________________________________________________________

//Geant headers
#include "G4LogicalVolume.hh"
#include "G4NistManager.hh"
#include "G4Cons.hh"
#include "G4SystemOfUnits.hh"
#include "G4PVPlacement.hh"
#include "G4FieldManager.hh"
#include "G4UniformMagField.hh"
#include "G4VisAttributes.hh"
#include "G4Tubs.hh"
#include "G4SubtractionSolid.hh"
#include "G4RotationMatrix.hh"
#include "G4DormandPrince745.hh"
#include "G4EqMagElectricField.hh"
#include "G4TransportationManager.hh"

//local headers
#include "beamPipe.h"


//_____________________________________________________________________________
beamPipe::beamPipe(G4String nam, G4double xpos,G4double ypos,G4double zpos,G4double length, G4double r1, G4double r2, G4double dout, G4double angle, G4LogicalVolume *top):
	Detector(), G4VSensitiveDetector(nam), fNam(nam) {

		G4RotationMatrix* yRot = new G4RotationMatrix;
		yRot->rotateY(angle*rad);

		G4String nam_inner = fNam+"_inner";
		G4Cons *shape_inner = new G4Cons(nam_inner, 0, r2, 0, r1, length/2, 0, 360*deg);

		G4Material *mat_inner = G4NistManager::Instance()->FindOrBuildMaterial("G4_Galactic");
		G4LogicalVolume *vol_inner = new G4LogicalVolume(shape_inner, mat_inner, nam_inner);
		vol_inner->SetVisAttributes( G4VisAttributes::GetInvisible() );

		//put the inner core to the top volume
		new G4PVPlacement(yRot, G4ThreeVector(xpos,ypos, zpos), vol_inner, nam_inner, top, false, 0);

		//cylindrical outer shape
		G4Tubs *shape_outer = new G4Tubs(fNam+"_outer", 0., dout, length/2-1e-4*meter, 0., 360.*deg);

		//magnet vessel around the inner magnetic core
		G4SubtractionSolid *shape_vessel = new G4SubtractionSolid(fNam, shape_outer, shape_inner);

		G4Material *mat_outer = G4NistManager::Instance()->FindOrBuildMaterial("G4_Be");
		G4LogicalVolume *vol_vessel = new G4LogicalVolume(shape_vessel, mat_outer, fNam);

		//vessel visibility
		G4VisAttributes *vis_vessel = new G4VisAttributes();
		vis_vessel->SetColor(0.25, 0.25, 0.25); // grey
		vis_vessel->SetLineWidth(2);
		vis_vessel->SetForceSolid(true);
		vol_vessel->SetVisAttributes(vis_vessel);

		//put the magnet vessel to the top volume
		new G4PVPlacement(yRot, G4ThreeVector(xpos, ypos, zpos), vol_vessel, fNam, top, false, 0);

	}//beamPipe

//_____________________________________________________________________________
G4bool beamPipe::ProcessHits(G4Step *step, G4TouchableHistory*) {

	//remove the track entering the magnet vessel
	//G4Track *track = step->GetTrack();
	//track->SetTrackStatus(fKillTrackAndSecondaries);

	return true;

}//ProcessHits




