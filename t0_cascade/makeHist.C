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


void makeHist(){

  auto outFileName = "dist.root";

  TFile* in = new TFile("feedthrough2.root");

  TH1F *r = new TH1F("r", "r", 100, 0, 800);
  TH1F *x = new TH1F("X", "X", 100, -350, 350);
  TH1F *y = new TH1F("Y", "Y", 100, 0, 600);
  TH1F *z = new TH1F("Z", "Z", 100, 0, 700);
  
  TH3F *dist = new TH3F("dist", "dist", 100, 0, 600, 100, 0, 600, 100, 0, 15*pow(10, 6));
  
  TTreeReader *myReader = new TTreeReader("ncapture", in);
  TTreeReaderValue<Double_t> xp(*myReader, "x");
  TTreeReaderValue<Double_t> yp(*myReader, "y");
  TTreeReaderValue<Double_t> zp(*myReader, "z");
  TTreeReaderValue<Double_t> tp(*myReader, "t");

  while(myReader->Next()){


    //x position = xp*100
    //y position = yp*100 + 340
    //z position = zp*100 + 350

    //r = sqrt[(xp - 2)^2 + (zp-3.5+1.303)^2]*100

    //cout << sqrt(pow((*xp -2),2) + pow((*zp+1.5),2))*100 << endl;
    r->Fill(sqrt(pow((*xp -2.091),2) + pow((*zp+2.203),2))*100);
    x->Fill(*xp*100);
    y->Fill(*yp*100 + 340);
    z->Fill(*zp*100 + 350);
    dist->Fill(sqrt(pow((*xp -2.091),2) + pow((*zp+2.203),2))*100, *yp*100 + 340, *tp);

  }

  TFile* out;
  out = new TFile(outFileName, "RECREATE");

  x->Write();
  y->Write();
  z->Write();
  r->Write();
  dist->Write();

  auto c1 = new TCanvas("c1", "c1");
  auto c2 = new TCanvas("c2", "c2");
  auto c3 = new TCanvas("c3", "c3");


  TH1* timeDist;
  TH1* ry;

  ry = dist->Project3D("yx");
  
  for( Int_t i = 0; i<1; i++){
    Double_t testX = x->GetRandom();
    Double_t testY = y->GetRandom();
    Double_t testZ = z->GetRandom();

    Double_t testR = sqrt(pow(testX-209.1,2) + pow(testZ+130.3,2));

    auto rAxis = dist->GetXaxis();
    auto yAxis = dist->GetYaxis();

    auto xbin = rAxis->FindBin(testR);
    auto ybin = yAxis->FindBin(testY);

    rAxis->SetRange(xbin-1,xbin+1);
    yAxis->SetRange(ybin-1,ybin+1);

    timeDist = dist->Project3D("z");

    Double_t testT = timeDist->GetRandom();

  
    cout << "r: " << testR << " cm\n" <<
      "x: "<< testX << " cm\n" <<
      "y: " << testY <<" cm\n" <<
      "z: " << testZ << " cm\n" <<
      "t: " << testT*pow(10,-3) << " us" << "\n\n" << endl;

  }
  
  c1->cd();

  ry->Draw("colz");

  c2->cd();

  timeDist->Draw();

  c3->cd();

  r->Draw();
    
  

}
