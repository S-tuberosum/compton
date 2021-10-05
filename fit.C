// fitting our data to the predicted plot
// assessing fit accuracy

#include "TCanvas.h"
#include "TObject.h"
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TF1.h"
#include "TLeaf.h"
#include "MyClass.h"

// double x_min = -451720;
// double x_max = -45150;

void fit()
{
    //TFile *f = TFile::Open(input);
    //TTree *t = (TTree*)f->Get("t");

//     TLeaf* hitX = GetLeaf("det.2_hits.x");
//     TLeaf* pXsec = GetLeaf("det.2_hits.x");
//     TLeaf* uXsec = GetLeaf("uXsec");

    //TGraph *a = new TGraph(?, det_2_hits_x, pXsec/uXsec);

    //a->Draw();

    auto f1 = TF1("f1", "(x-[2])/[3]", -451720, -45150);

    f1.SetParameter(2, -45150); // value of x where E = E_max 
    f1.SetParameter(3, -45150 - -451720); // del x, difference between max and min of x

    Double_t a = 1/(1 + (4*2.33*7e9)/(510998.95*510998.95)); // kinematic factor 

    auto aLong = TF1("aLong", "[1]*(1-x*(1+[0]))*((1-1/((1-x*(1-[0]))*(1-x*(1-[0]))))) / \
    (((x*(1-[0]))*(x*(1-[0])))/(1-x*(1-[0])) + 1 + ((1-x*(1+[0]))/(1-x*(1-[0]))* \
    ((1-x*(1+[0]))/(1-x*(1-[0])))))", -451720, -45150); // longitudinal asymmetry 

    aLong.SetParameter(0, a);
    aLong.SetParameter(1, 1); // polarization

    auto g = TF1("g", "aLong(f1(x))");

    //aa->Fit(g)
    //t->Draw("pXsec/uXsec:det.2_hits.x", "det.2_hits.x > -451720 & det.2_hits.x < -45150", "prof"); // profile plot of long asymmetry

}

