/* Reads the points from a file and produces a simple graph. */
int macro2(){
  int i = 1128;

  TCanvas* c = new TCanvas("D", "D", 1200, 1200);
  c.SetLeftMargin(0.13);
  c.SetTopMargin(0.02);
  c.SetRightMargin(0.02);
  
  TFile f(Form("Alpha2-%i - all.root",i));
  SpecD.SetLineColor(kRed);
  //SpecD.DrawCopy();
  TH1F h(*SpecD);
  h.SetLineColor(kRed);
  TFile g(Form("Alpha2-%i - 1.root",i));
  h.Add(SpecD, -1);
  SpecD.DrawCopy("");
  h.DrawCopy("Same");


  TLegend leg (.13 ,.98 ,.3 ,.9);
  leg.SetFillColor(0);
  SpecD.SetLineWidth(3);
  h.SetLineWidth(3);
  leg.AddEntry(&h, "#alpha_{0}");
  leg.AddEntry(SpecD, "#alpha_{1}");
  leg.DrawClone();
  
  c.SaveAs(Form("%i-spec-D-mix.pdf",i));

  TCanvas* d = new TCanvas("T", "T", 1200, 1200);
  d.SetLeftMargin(0.13);
  d.SetTopMargin(0.02);
  d.SetRightMargin(0.02);
  
  TFile f0(Form("Alpha2-%i - all.root",i));
  TH1F all(*SpecT);
  
  TFile g0(Form("Alpha2-%i - 0.root",i));
  all.Add(SpecT,-1);
  all.GetYaxis() -> SetRangeUser(0, all.GetMaximum());
  
  if (all.GetMaximum() > SpecT.GetMaximum()) {
    all.DrawCopy("");
  } else {
    SpecT.DrawCopy("");
  }
  SpecT.SetLineColor(kRed);
  all.DrawCopy("SAME");
  SpecT.DrawCopy("SAME");
  d.RedrawAxis();

  TLegend leg0 (.13 ,.98 ,.3 ,.9) ;
  leg0.SetTextFont(132);
  leg0.SetFillColor(0);
  SpecT.SetLineWidth(3);
  all.SetLineWidth(3);
  leg0.AddEntry(SpecT, "#alpha_{0}");
  leg0.AddEntry(&all, "#alpha_{1}");
  leg0.DrawClone();
  
  d.SaveAs(Form("%i-spec-T-mix.pdf",i));
}
