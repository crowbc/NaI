void buildSpectrum()
{
	TH1I* spectrum = new TH1I("spectrum", "Hits", 100, 1, 101);
	
	fstream file;
	file.open("NaIoutput.root", ios::in);
	int hits;
	
	while(1)
	{
		file >> hits;
		spectrum->Fill(hits);
		if(file.eof()) break;
	}
	
	file.close();
	
	spectrum->GetXaxis()->SetTitle("NaI PMT hits");
	spectrum->GetYaxis()->SetTitle("number of events");
	
	spectrum->SetDrawOption("G");
	
	TCanvas* c1 = new TCanvas();
	spectrum->Draw();
}
