#include <TFile.h>
#include <TTree.h>
#include <TH1.h>
#include <TF1.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TLeaf.h>
#include <Rtypes.h>
#include <TROOT.h>
#include <TRandom3.h>
#include <TH2.h>
#include <TPad.h>
#include <TVector3.h>
#include <TString.h>
#include <TPRegexp.h>
#include <TGraph.h>
#include <TSystemDirectory.h>
#include <TSystemFile.h>
#include <TSystem.h>
#include <TList.h>
#include <TGraph.h>
#include <TStopwatch.h>

#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

void dist() {

    // Open root file containing position distributions
  TFile* f = new TFile("feedthrough2.root");

  //Extract necessary histograms from the file
  TH1F *x = new TH1F("X", "X", 100, -350, 350);
  TH1F *y = new TH1F("Y", "Y", 100, 0, 600);
  TH1F *z = new TH1F("Z", "Z", 100, 0, 700);

  TH2F *yz = new TH2F("Neutron Capture Distribution", "Neutron Capture Distribution", 100, 0, 600, 100, 0, 700);

  TTreeReader *myReader = new TTreeReader("ncapture", f);
  TTreeReaderValue<Double_t> xp(*myReader, "x");
  TTreeReaderValue<Double_t> yp(*myReader, "y");
  TTreeReaderValue<Double_t> zp(*myReader, "z");

  while(myReader->Next()){

    x->Fill(*xp*100);
    y->Fill(*yp*100 + 340);
    z->Fill(*zp*100 + 350);

    yz->Fill(*zp*100 + 350, *yp*100 + 340);

  }

  auto c1 = new TCanvas("c1", "c1");

  c1->cd();

  yz->Draw("COLZ");
  yz->GetYaxis()->SetTitle("Y position (cm)");
  yz->GetXaxis()->SetTitle("Z position (cm)");

}
