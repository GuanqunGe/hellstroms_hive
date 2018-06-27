#include "bdt_datamc.h"

int bdt_datamc::plotStacks(TFile *ftest, bdt_variable var,double c1, double c2){
	std::cout << "Plotting stack" << std::endl;
	TCanvas *cobs = new TCanvas("","",900,800);
	//TCanvas *cobs = new TCanvas("","",1800,1600);
	//cobs->Divide(2,2,0.0025,0.0000001);

	double plot_pot=4.801e19;

	double title_size_ratio=0.1;
	double label_size_ratio=0.1;
	double title_offset_ratioY = 0.3 ;
	double title_offset_ratioX = 1.1;

	double title_size_upper=0.15;
	double label_size_upper=0.05;
	double title_offset_upper = 1.45;


	ftest->cd();
	THStack* s0 = mc_stack->getStack(var,0,-9,-9);
	THStack* s1 = mc_stack->getStack(var,1,-9,-9);
	THStack* s2 = mc_stack->getStack(var,2,c1,-9);
	THStack* s3 = mc_stack->getStack(var,3,c1, c2);

	std::cout<<"Gotten all stacks."<<std::endl;
	TH1* sh0 = mc_stack->getSum(var,0,-9,-9);
	TH1* sh1 = mc_stack->getSum(var,1,-9,-9);
	TH1* sh2 = mc_stack->getSum(var,2,c1,-9);
	TH1* sh3 = mc_stack->getSum(var,3,c1, c2);

	std::string dat_cut_0 =	data_file->getStageCuts(0, -9, -9);
	std::string dat_cut_1 =	data_file->getStageCuts(1, -9,-9);
	std::string dat_cut_2 =	data_file->getStageCuts(2, c1, -9);
	std::string dat_cut_3 =	data_file->getStageCuts(3, c1, c2);

	std::cout<<dat_cut_1<<" CUTPRE"<<std::endl;
	TH1 * d0 = data_file->getTH1(var, dat_cut_0, "d0_"+data_file->tag+"_"+var.safe_name, plot_pot);
	TH1 * d1 = data_file->getTH1(var, dat_cut_1, "d1_"+data_file->tag+"_"+var.safe_name, plot_pot);
	TH1 * d2 = data_file->getTH1(var, dat_cut_2, "d2_"+data_file->tag+"_"+var.safe_name, plot_pot);
	TH1 * d3 = data_file->getTH1(var, dat_cut_3, "d3_"+data_file->tag+"_"+var.safe_name, plot_pot);

	std::cout<<"Gotten all data hists."<<std::endl;

	std::vector<THStack*> vec_stacks = {s0,s1,s2,s3};	
	std::vector<TH1*> vec_th1s = {sh0,sh1,sh2,sh3};	
	std::vector<std::string> data_cuts = {dat_cut_0, dat_cut_1, dat_cut_2, dat_cut_3};
	std::vector<TH1*> data_th1s = {d0,d1,d2,d3};
	std::vector<std::string> stage_name = {"All Vertices","Pre-Selection","Post Cosmic BDT","Post BNB BDT"};


	for(int k = 0; k<4; k++){
    // Change k to number of stage if not using for loop
    //int k = 0;
        std::cout << k << std::endl;
        //std::string stageNum = std::to_string(k);
		//cobs->cd(k+1);
		cobs->cd();
		TPad *pad0top = new TPad(("pad0top_"+stage_name.at(k)).c_str(), ("pad0top_"+stage_name.at(k)).c_str(), 0, 0.35, 1, 1.0);
		pad0top->SetBottomMargin(0); // Upper and lower plot are joined
		pad0top->Draw();             // Draw the upper pad: pad2top
		pad0top->cd();               // pad2top becomes the current pad

		double rmin = 0;
		double rmax = 3;
		int data_rebin = 1;
		if(k==0 || k == 1){
			rmin=0.3; rmax = 1.499;
		}else if(k==2){ data_rebin = 2;}else if(k==3){data_rebin=4;};


		vec_stacks.at(k)->SetMaximum(vec_th1s.at(k)->GetMaximum()*1.4);
		vec_stacks.at(k)->SetMinimum(0.0001);
		vec_stacks.at(k)->Draw("hist");
		vec_stacks.at(k)->SetTitle(stage_name.at(k).c_str());
		vec_stacks.at(k)->GetXaxis()->SetTitle(var.unit.c_str());
		vec_stacks.at(k)->GetYaxis()->SetTitle("Vertices");
		vec_stacks.at(k)->GetYaxis()->SetTitleOffset(1.5);
		vec_stacks.at(k)->SetMaximum( std::max(vec_th1s.at(k)->GetMaximum(), data_th1s.at(k)->GetMaximum()*1.4));
		vec_stacks.at(k)->SetMinimum(0.0001);


		TLegend *l0 = new TLegend(0.11,0.72,0.89,0.89);
		l0->SetNColumns(2);
		double NeventsStack = 0;

		for(auto &f: mc_stack->stack){
			double Nevents = f->GetEntries( f->getStageCuts(k,c1,c2).c_str())*(plot_pot/f->pot )*f->scale_data;
			NeventsStack+=Nevents;
			auto h1 = new TH1F(("tmp"+stage_name.at(k)+var.safe_name+f->tag).c_str(),"TLegend Example",200,-10,10);
			h1->SetFillColor(f->col);
			h1->SetFillStyle(f->fillstyle);
			h1->SetLineColor(kBlack);
			l0->AddEntry(h1,("#splitline{"+f->plot_name+"}{"+to_string_prec(Nevents,2)+"}").c_str(),"f");
		}

		//data_th1s.at(k)->Rebin(data_rebin);
		data_th1s.at(k)->SetMarkerStyle(20);
		data_th1s.at(k)->SetLineColor(kBlack);
		data_th1s.at(k)->Draw("same E1");

		vec_stacks.at(k)->SetMaximum( std::max(vec_th1s.at(k)->GetMaximum(), data_th1s.at(k)->GetMaximum()*1.4));

		double NdatEvents = data_file->GetEntries(data_cuts.at(k).c_str())*(plot_pot/data_file->pot )*data_file->scale_data;

		l0->AddEntry(data_th1s.at(k),("#splitline{"+data_file->tag+"}{"+to_string_prec(NdatEvents,2)+"}").c_str(),"lp");	

		l0->Draw();
		l0->SetLineWidth(0);
		l0->SetLineColor(0);
		l0->SetFillStyle(0);
		l0->SetTextSize(0.03);

		//cobs->cd(k+1);	
		cobs->cd();
		TPad *pad0bot = new TPad(("padbot_"+stage_name.at(k)).c_str(),("padbot_"+stage_name.at(k)).c_str(), 0, 0.05, 1, 0.35);
		pad0bot->SetTopMargin(0);
		pad0bot->SetBottomMargin(0.351);
		pad0bot->SetGridx(); // vertical grid
		pad0bot->Draw();
		pad0bot->cd();       // pad0bot becomes the current pad

		TH1* ratpre = (TH1*)data_th1s.at(k)->Clone(("ratio_"+stage_name.at(k)).c_str());
		ratpre->Sumw2();
		//vec_th1s.at(k)->Rebin(data_rebin);
		ratpre->Divide(vec_th1s.at(k));		

		ratpre->SetFillColor(kGray+1);
		ratpre->SetMarkerStyle(2);
		ratpre->SetFillStyle(3144);
		ratpre->Draw("E2");	


		TLine *line = new TLine(ratpre->GetXaxis()->GetXmin(),1.0,ratpre->GetXaxis()->GetXmax(),1.0 );
		line->Draw("same");
		ratpre->SetLineColor(kBlack);
		ratpre->SetTitle("");
		ratpre->GetYaxis()->SetTitle("Ratio");
		ratpre->GetXaxis()->SetTitleOffset(title_offset_ratioX);
		ratpre->GetYaxis()->SetTitleOffset(title_offset_ratioY);
		ratpre->SetMinimum(rmin);	
		ratpre->SetMaximum(rmax);//ratpre->GetMaximum()*1.1);
		ratpre->GetYaxis()->SetTitleSize(title_size_ratio);
		ratpre->GetXaxis()->SetTitleSize(title_size_ratio);
		ratpre->GetYaxis()->SetLabelSize(label_size_ratio);
		ratpre->GetXaxis()->SetLabelSize(label_size_ratio);
		ratpre->GetXaxis()->SetTitle(var.unit.c_str());

		std::string mean = "Norm: "+to_string_prec(NdatEvents/NeventsStack*100,1)+ "%";
		TText *t = new TText(0.14,0.9,mean.c_str());
		t->SetNDC();
		t->SetTextColor(kRed-7);
		//t->SetTextFont(43);
		t->SetTextSize(0.12);
		t->Draw("same");
	
	//var_precut.front()->GetYaxis()->SetRangeUser(0.1,ymax_pre);
	//var_precut.front()->GetYaxis()->SetTitle("Verticies");

	if(false){
		data_file->tvertex->Scan("run_number:subrun_number:event_number:reco_shower_dedx_plane2[0]:reco_shower_helper_energy[0]:reco_track_displacement[0]:shortest_asso_shower_to_vert_dist",dat_cut_3.c_str());

	}

        cobs->Write();
        //cobs->SaveAs(("datamc/"+tag+"_"+data_file->tag+"_"+var.safe_name+"_stage_"+std::to_string(k)+".pdf").c_str(),"pdf");
        cobs->SaveAs(("datamc/"+tag+"_"+data_file->tag+"_"+var.safe_name+"_stage_"+std::to_string(k)+".pdf").c_str(),"pdf");
        // To avoid renaming everything in the technote
        if (k ==1 )
	        cobs->SaveAs(("datamc/"+tag+"_"+data_file->tag+"_"+var.safe_name+".pdf").c_str(),"pdf"); 
    }

	return 0;
}


int bdt_datamc::plotBDTStacks(TFile *ftest, bdt_info whichbdt,double c1, double c2){
	std::cout << "Plotting BDT stacks" << std::endl;
	TCanvas *cobs = new TCanvas("","",900,800);
	cobs->cd();
	cobs->Divide(2,1,0.0025,0.0000001);
	double plot_pot=4.801e19;

	double title_size_ratio=0.1;
	double label_size_ratio=0.1;
	double title_offset_ratioY = 0.3 ;
	double title_offset_ratioX = 1.1;

	double title_size_upper=0.149;
	double label_size_upper=0.05;
	double title_offset_upper = 1.45;

	ftest->cd();
	THStack* s0 = mc_stack->getBDTStack(whichbdt,0,-9,-9);
	THStack* s1 = mc_stack->getBDTStack(whichbdt,1,-9,-9);
	THStack* s2 = mc_stack->getBDTStack(whichbdt,2,c1,-9);
	THStack* s3 = mc_stack->getBDTStack(whichbdt,3,c1, c2);

	std::string dat_cut_0 =	data_file->getStageCuts(0, -9, -9);
	std::string dat_cut_1 =	data_file->getStageCuts(1, -9,-9);
	std::string dat_cut_2 =	data_file->getStageCuts(2, c1, -9);
	std::string dat_cut_3 =	data_file->getStageCuts(3, c1, c2);


	std::vector<THStack*> vec_stacks = {s0,s1,s2,s3};	
	std::vector<std::string> data_cuts = {dat_cut_0, dat_cut_1, dat_cut_2, dat_cut_3};


	std::vector<std::string> stage_name = {"All Vertices","Pre-Selection","Post Cosmic BDT","Post BNB BDT"};

    int k = 0;
	for (k = 0; k < 4; k++) {
		std::cout<<"On stage: "<<k<<" of bdt_datamc::plotBDTStacks."<<std::endl;	
		bdt_variable dvar = data_file->getBDTVariable(whichbdt);

		TH1* summed = mc_stack->getBDTSum(whichbdt, k,c1,c2);

		TH1* data = data_file->getTH1(dvar, data_cuts.at(k), std::to_string(k)+"_"+whichbdt.identifier+"_"+data_file->tag+"_"+dvar.safe_name, plot_pot);
		std::cout << "Got data" << std::endl;


		//cobs->cd(k+1);
		cobs->cd();
		TPad *pad0top = new TPad(("pad0top_"+stage_name.at(k)).c_str(), ("pad0top_"+stage_name.at(k)).c_str(), 0, 0.35, 1, 1.0);
		pad0top->SetLogy();
		pad0top->SetBottomMargin(0); // Upper and lower plot are joined
		pad0top->Draw();             // Draw the upper pad: pad2top
		pad0top->cd();               // pad2top becomes the current pad

		vec_stacks.at(k)->SetMaximum(summed->GetMaximum()*5);
		//		vec_stacks.at(k)->SetMinimum(0.0001);
		vec_stacks.at(k)->Draw("hist");
		vec_stacks.at(k)->SetTitle(stage_name.at(k).c_str());
		vec_stacks.at(k)->GetXaxis()->SetTitle(dvar.unit.c_str());
		vec_stacks.at(k)->GetYaxis()->SetTitle("Vertices");
		vec_stacks.at(k)->GetYaxis()->SetTitleOffset(1.5);
		vec_stacks.at(k)->SetMaximum(summed->GetMaximum()*10);
		vec_stacks.at(k)->SetMinimum(0.1);
		//		vec_stacks.at(k)->SetMinimum(0.0001);

		TLegend *l0 = new TLegend(0.11,0.72,0.89,0.89);
		l0->SetNColumns(2);

		double NeventsStack = 0;


		for(auto &f: mc_stack->stack){
			double Nevents = f->GetEntries( f->getStageCuts(k,c1,c2).c_str())*(plot_pot/f->pot )*f->scale_data;
			auto h1 = new TH1F(("tmp"+stage_name.at(k)+dvar.name+f->tag).c_str(),"TLegend Example",200,-10,10);

			NeventsStack+=Nevents;
			h1->SetFillColor(f->col);
			h1->SetFillStyle(f->fillstyle);
			h1->SetLineColor(kBlack);
			l0->AddEntry(h1,("#splitline{"+f->plot_name+"}{"+to_string_prec(Nevents,2)+"}").c_str(),"f");
		}

		data->SetMarkerStyle(20);
		data->Draw("same E1");
		double NdatEvents = data_file->GetEntries(data_cuts.at(k).c_str())*(plot_pot/data_file->pot )*data_file->scale_data;
		l0->AddEntry(data,("#splitline{"+data_file->plot_name+"}{"+to_string_prec(NdatEvents,2)+"}").c_str(),"lp");	

		l0->Draw();
		l0->SetLineWidth(0);
		l0->SetLineColor(0);
		l0->SetFillStyle(0);
		l0->SetTextSize(0.03);

		//cobs->cd(k+1);	
		cobs->cd();
		TPad *pad0bot = new TPad(("padbot_"+stage_name.at(k)).c_str(),("padbot_"+stage_name.at(k)).c_str(), 0, 0.05, 1, 0.35);
		pad0bot->SetTopMargin(0);
		pad0bot->SetBottomMargin(0.351);
		pad0bot->SetGridx(); // vertical grid
		pad0bot->Draw();
		pad0bot->cd();       // pad0bot becomes the current pad

		TH1* ratpre = (TH1*)data->Clone(("ratio_"+stage_name.at(k)).c_str());

		ratpre->Divide(summed);		
		ratpre->SetFillColor(kGray+1);
		ratpre->SetMarkerStyle(2);
		ratpre->SetFillStyle(3144);
		ratpre->Draw("E2");	

		TLine *line = new TLine(ratpre->GetXaxis()->GetXmin(),1.0,ratpre->GetXaxis()->GetXmax(),1.0 );
		line->Draw("same");
		ratpre->SetLineColor(kBlack);
		ratpre->SetTitle("");
		ratpre->GetYaxis()->SetTitle("Ratio");
		ratpre->GetXaxis()->SetTitleOffset(title_offset_ratioX);
		ratpre->GetYaxis()->SetTitleOffset(title_offset_ratioY);
		ratpre->SetMinimum(0.0);	
		ratpre->SetMaximum(1.99);
		ratpre->GetYaxis()->SetTitleSize(title_size_ratio);
		ratpre->GetXaxis()->SetTitleSize(title_size_ratio);
		ratpre->GetYaxis()->SetLabelSize(label_size_ratio);
		ratpre->GetXaxis()->SetLabelSize(label_size_ratio);
		ratpre->GetXaxis()->SetTitle(dvar.unit.c_str());
		//var_precut.front()->GetYaxis()->SetRangeUser(0.1,ymax_pre);
		//var_precut.front()->GetYaxis()->SetTitle("Vertices");

		std::string mean = "Norm: "+to_string_prec(NdatEvents/NeventsStack*100,1)+ "%";
		TText *t = new TText(0.241,1.3,mean.c_str());
		t->SetTextColor(kRed-7);
		//t->SetTextFont(43);
		t->SetTextSize(0.12);
		//t->Draw("same");

        cobs->Write();
        //cobs->SaveAs(("datamc2/"+tag+"_"+data_file->tag+"_BDTVAR_"+whichbdt.identifier+".png").c_str(),"png");
        cobs->SaveAs(("datamc2/"+tag+"_"+data_file->tag+"_BDTVAR_"+whichbdt.identifier+"_stage_"+std::to_string(k)+".pdf").c_str(),"pdf");
        //cobs->SaveAs(("datamc/"+var.name+".png").c_str(),"png");
    }

	return 0;
}


