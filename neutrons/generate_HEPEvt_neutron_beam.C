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

void generate_HEPEvt_neutron_beam(UInt_t nNeutrons, UInt_t nPulses){
  //Prvent canvases from being drawn
  gROOT->Reset();

  TStopwatch* clock = new TStopwatch();
  clock->Start();

  //Random and vertex parameters
  TRandom3* rdef = new TRandom3();//random number generator
  rdef->SetSeed(0);

  //Define some parameters
  Double_t beamWidth = 12.0; //width of beam window
  Double_t beamHeight = 12.0; //heigt of beam window
  Int_t nbNeutrons = nNeutrons;
  Int_t nbPulses = nPulses;
  Double_t plane_Z = 350; //location of the beam window center
  Double_t plane_X = 0; //
  Double_t plane_Y = 400; //
  Double_t neutronE = 2.5; //MeV

  //HEPEvt file
  std::ofstream output("neutrons.dat");

  //Postion
  TVector3 Xn, Pn;
  Xn.SetXYZ(0.,0.,0.);
  Pn.SetXYZ(0.,-neutronE*1e-3,0.);//give all neutrons downward momentum

  for(UInt_t i = 0; i<nPulses; i++){
    //write first line for each pulse
    output << i << " " << nNeutrons << endl;
    
    for(UInt_t n = 0; n<nNeutrons; n++){

      //generate random position from the beam window area
      Xn.SetXYZ(rdef->Uniform(plane_X - beamWidth/2, plane_X + beamWidth/2),
		plane_Y,
		rdef->Uniform(plane_Z - beamHeight/2, plane_Z + beamHeight/2));

      // write in HEPEvt file
      output << "1 2112 0 0 0 0 "
	     << Pn[0] << " " << Pn[1] << " " << Pn[2] << " " << neutronE*1e-3 << " 0 "
	     << Xn[0] << " " << Xn[1] << " " << Xn[2] << " 0 0 0 " << endl;
    
    }//end of neutron loop
  }//end of pulse loop

  cout << "Done! And in " << clock->RealTime() << " s." << endl;
}
