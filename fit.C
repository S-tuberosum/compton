// fitting our data to the predicted plot
// assessing fit accuracy

void fit()
{
    int x_min = -451715;
    int x_max = -451500;

    auto f1 = TF1("f1", "(x-[2])/[3]", x_min, x_max, "GL");

    Double_t a = 1/(1 + (4*2.33*7e9)/(510998.95*510998.95)); // kinematic factor

    auto aLong = TF1("aLong", "[1]*(1-x*(1+[0]))*((1-1/((1-x*(1-[0]))*(1-x*(1-[0]))))) / \
    (((x*(1-[0]))*(x*(1-[0])))/(1-x*(1-[0])) + 1 + ((1-x*(1+[0]))/(1-x*(1-[0]))* \
    ((1-x*(1+[0]))/(1-x*(1-[0])))))", x_min, x_max, "GL"); // longitudinal asymmetry

    auto g = TF1("g", "aLong(f1(x))", x_min, x_max);

    TFile *input = new TFile("bP_0.2.root", "read");
    TTree *t = (TTree*)input->Get("t");

    g.FixParameter(0, a);
    g.SetParameter(1, 1); // polarization
    g.SetParLimits(1, 0, 1);

    g.SetParameter(2, -451500); // value of x where E = E_max
    //g.SetParLimits(2, -451500, -451450);
    g.SetParameter(3, 451500-451720); // del x, difference between max and min of x

    gStyle->SetOptFit(1);
    t->Draw("pXsec/uXsec:det.2_hits.x", "det.2_hits.x > -451715 & det.2_hits.x < -451500", "prof"); // profile plot of long asymmetry
    t->Fit("g", "", "", "-451715", "-451500");
    g.Draw("same");
}
