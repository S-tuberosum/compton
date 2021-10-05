// fitting our data to the predicted plot
// assessing fit accuracy

#include "TCanvas.h"
#include "TObject.h"
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TF1.h"
#include "TLeaf.h"


auto f1 = TF1("f1", "(x-[2])/[3]", -451720, -45150, "GL");

Double_t a = 1/(1 + (4*2.33*7e9)/(510998.95*510998.95)); // kinematic factor

auto aLong = TF1("aLong", "[1]*(1-x*(1+[0]))*((1-1/((1-x*(1-[0]))*(1-x*(1-[0]))))) / \
(((x*(1-[0]))*(x*(1-[0])))/(1-x*(1-[0])) + 1 + ((1-x*(1+[0]))/(1-x*(1-[0]))* \
((1-x*(1+[0]))/(1-x*(1-[0])))))", -451720, -45150, "GL"); // longitudinal asymmetry

auto g = TF1("g", "aLong(f1(x))", -451720, -45150, "GL");

void fit()
{
    f1.SetParameter(2, -45150); // value of x where E = E_max 
    f1.SetParameter(3, 220); // del x, difference between max and min of x
    f1.GetParameter(2);

    aLong.SetParameter(0, a);
    aLong.SetParameter(1, 1); // polarization

    //t->Draw("pXsec/uXsec:det.2_hits.x", "det.2_hits.x > -451720 & det.2_hits.x < -45150", "prof"); // profile plot of long asymmetry
}
