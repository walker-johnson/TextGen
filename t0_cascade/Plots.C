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


void Plots(){

  auto inFile = "reco0.root";
  auto outFile = "myPlots.root";

  TFile* in = new TFile(inFile);

  TH1F *sliceE = new TH1F("reco_slice_e", "Reconstructed Slice Energy",
			  100, 0, 8);
  TH1I *nSlices = new TH1I("reco_n_slices", "Slices Reconstructed Per Pulse",
			   14, 0, 14);
  TH1F *xReco = new TH1F("reco_slice_x", "Reconstructed Slice Position in x",
			 100, -350, 350);


  TTreeReader *myReader = new TTreeReader("nfinder/calibration", in);

  TTreeReaderArray<double> rSliceE(*myReader, "fEdepSlice_reco");
  TTreeReaderArray<int> rNSlices(*myReader, "fNumberOfSlices");
  TTreeReaderArray<double> rXReco(*myReader, "fSlice_reco_x");

  while(myReader->Next()){

    for(auto s : rSliceE){
      sliceE->Fill(s);
    }

    for(auto s : rNSlices){
      nSlices->Fill(s);
    }

    for(auto s : rXReco){
      xReco->Fill(s);
    }
  }

  

  TFile* out = new TFile(outFile, "RECREATE");

  sliceE->Write();
  nSlices->Write();
  xReco->Write();

  auto c1 = new TCanvas("c1", "c1");
  auto c2 = new TCanvas("c2", "c2");
  auto c3 = new TCanvas("c3", "c3");

  c1->cd();
  sliceE->Draw();

  c2->cd();
  nSlices->Draw();

  c3->cd();
  xReco->Draw();

  
  
  

  
  
  

}
