// C++ includes
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <exception>
#include <tuple>
#include <stdexcept>

// Root includes
#include "TInterpreter.h"
#include "TROOT.h"
#include "TH1.h"
#include "TH2.h"
#include "TTree.h"
#include "TBranch.h"
#include "TStreamer.h"
#include "TFile.h"
#include "TNtuple.h"
#include "TClonesArray.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TLine.h"
#include "TLegend.h"
#include "TStyle.h"
#include "THStack.h"
#include "TVector3.h"
#include "TMath.h"
#include "TString.h"
#include "TF1.h"
#include "TProfile.h"
#include "TPaveText.h"

// Define bin ranges for projection histograms
// Each bin is 10 MeV, so the energy range will be bin_num/10
// Ex: To project between 100 and 150 MeV, use (10, 15) as bin numbers
//std::vector<std::pair<int,int> > leadingProjBins() {
//    std::vector<std::pair<int,int> > ranges;
std::vector<std::pair<int,int> > leadingProjBins() {
    std::vector<std::pair<int,int> > ranges;
    // v26.5
    ranges.push_back(std::make_pair(3, 4) );
    ranges.push_back(std::make_pair(4, 5) );
    ranges.push_back(std::make_pair(5, 6) );
    ranges.push_back(std::make_pair(6, 8) );
    ranges.push_back(std::make_pair(8, 10) );
    ranges.push_back(std::make_pair(10, 12) );
    ranges.push_back(std::make_pair(12, 14) );
    ranges.push_back(std::make_pair(14, 16) );
    ranges.push_back(std::make_pair(16, 18) );
    ranges.push_back(std::make_pair(18, 20) );
    ranges.push_back(std::make_pair(20, 22) );
    ranges.push_back(std::make_pair(22, 24) );
    ranges.push_back(std::make_pair(24, 26) );
    ranges.push_back(std::make_pair(26, 28) );
    ranges.push_back(std::make_pair(28, 31) );
    ranges.push_back(std::make_pair(31, 34) );
    ranges.push_back(std::make_pair(34, 37) );
    ranges.push_back(std::make_pair(37, 40) );
    return ranges;
}




















