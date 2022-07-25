#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH1.h"

void getSpectrum()
{
	// read the given tree file and fill spectrum histogram. Draw spectrum histogram and save image of graph.
	TString prefix = "NaIoutput";
	TString ext = ".root";
	TString numEvt = "100M";
	TString isotope = "Co60";
	TString fName = prefix+numEvt+isotope+ext;
	
	TFile *f1 = new TFile(fName);
	TTree *Hits = (TTree*)f1->Get("Hits");
	TH1I *h1 = new TH1I("h1", isotope+" Spectrum", 10000, 0, 200000001);
	TCanvas *c1 = new TCanvas();
	int tt, numEnt;
	
	numEnt=Hits->GetEntries();
	Hits->SetBranchAddress("fEvent", &tt);
	
	for(int i=0; i<numEnt; i++)
	{
		Hits->GetEntry(i);
		h1->Fill(tt);
	}
	
	h1->Draw();
}
