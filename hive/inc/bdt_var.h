#ifndef BDT_VAR_H
#define BDT_VAR_H

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
/******** Our includes *****/

/******** Root includes *****/

#include "TTreeFormula.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TH1.h"
#include "TH1D.h"
#include "TLine.h"
#include "TMVA/Types.h"
#include "TMVA/DataLoader.h"
#include "TMVA/Reader.h"
#include "TFriendElement.h"


struct bdt_variable{

	public:
		std::string name;
        int id;
		std::string safe_name;
		std::string binning;
		std::string unit;
		std::string safe_unit;
		bool is_track;
		std::string type;
        bool is_logplot;

        std::vector<double> edges;

		bdt_variable(std::string inname, std::string inbin, std::string inunit,bool intrack, std::string intype) : bdt_variable(inname,inbin,inunit,intrack,intype,-1){}; 
		
        bdt_variable(std::string inname, std::string inbin, std::string inunit,bool intrack, std::string intype,int in_id) : 
			name(inname), 
			binning(inbin),
			unit(inunit),
			is_track(intrack),
			type(intype),
            id(in_id),
            is_logplot(false)
		{
			safe_name = name;
			safe_name.erase(std::remove(safe_name.begin(), safe_name.end(), '('), safe_name.end());
			safe_name.erase(std::remove(safe_name.begin(), safe_name.end(), ')'), safe_name.end());
			safe_name.erase(std::remove(safe_name.begin(), safe_name.end(), '\\'), safe_name.end());
			safe_name.erase(std::remove(safe_name.begin(), safe_name.end(), '/'), safe_name.end());
			safe_name.erase(std::remove(safe_name.begin(), safe_name.end(), '['), safe_name.end());
			safe_name.erase(std::remove(safe_name.begin(), safe_name.end(), ']'), safe_name.end());
			safe_name.erase(std::remove(safe_name.begin(), safe_name.end(), '+'), safe_name.end());
			safe_name.erase(std::remove(safe_name.begin(), safe_name.end(), '-'), safe_name.end());
			safe_name.erase(std::remove(safe_name.begin(), safe_name.end(), '*'), safe_name.end());
			safe_name.erase(std::remove(safe_name.begin(), safe_name.end(), '.'), safe_name.end());
			safe_name.erase(std::remove(safe_name.begin(), safe_name.end(), ' '), safe_name.end());
			safe_name.erase(std::remove(safe_name.begin(), safe_name.end(), ','), safe_name.end());
			safe_name.erase(std::remove(safe_name.begin(), safe_name.end(), '|'), safe_name.end());
	
           	safe_unit = unit;
			safe_unit.erase(std::remove(safe_unit.begin(), safe_unit.end(), ' '), safe_unit.end());
			safe_unit.erase(std::remove(safe_unit.begin(), safe_unit.end(), '('), safe_unit.end());
			safe_unit.erase(std::remove(safe_unit.begin(), safe_unit.end(), ')'), safe_unit.end());
			safe_unit.erase(std::remove(safe_unit.begin(), safe_unit.end(), '\\'), safe_unit.end());
			safe_unit.erase(std::remove(safe_unit.begin(), safe_unit.end(), '/'), safe_unit.end());
			safe_unit.erase(std::remove(safe_unit.begin(), safe_unit.end(), '['), safe_unit.end());
			safe_unit.erase(std::remove(safe_unit.begin(), safe_unit.end(), ']'), safe_unit.end());
			safe_unit.erase(std::remove(safe_unit.begin(), safe_unit.end(), '+'), safe_unit.end());
			safe_unit.erase(std::remove(safe_unit.begin(), safe_unit.end(), '-'), safe_unit.end());
			safe_unit.erase(std::remove(safe_unit.begin(), safe_unit.end(), '*'), safe_unit.end());
			safe_unit.erase(std::remove(safe_unit.begin(), safe_unit.end(), '|'), safe_unit.end());
	

            std::string bins = binning;
            edges.clear();


            bins.erase(std::remove(bins.begin(), bins.end(), '('), bins.end());
            bins.erase(std::remove(bins.begin(), bins.end(), ')'), bins.end());

            size_t pos = 0;
            std::string delim = ",";
            std::string token;
            while ((pos = bins.find(delim)) != std::string::npos) {
                token = bins.substr(0, pos);
                edges.push_back(std::stod(token));
                bins.erase(0, pos + delim.length());
            }
            edges.push_back(std::stod(bins));
            



		};

		bdt_variable(){};

		bdt_variable(std::string inname, std::string inbin, std::string inunit,bool intrack) : 
			name(inname), 
			binning(inbin),
			is_track(intrack),
			unit(inunit)
	{};

};





#endif