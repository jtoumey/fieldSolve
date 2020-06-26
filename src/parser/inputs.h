//
//  inputs.h
//  flowSolve
//
//  Created by Julian Toumey on 6/15/20.
//

#ifndef INPUTS_H
#define INPUTS_H

#include "boundingBox.h"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

class Inputs
{
private:
    
    // Main input file name
    std::string inputFileName;
    
    std::vector<std::string> inputKeys = {"dimension", "x1Min", "x1Max",
        "x2Min", "x2Max", "x1Cells", "x2Cells"};
    
public:
    double simDimension;
    BoundingBox domainBbox;
    int x1Cells, x2Cells;
    
public:
    /// Constructor with file handle
    Inputs(std::string inputFileName_);
    
    /// Check file existence
    int checkFileExistence(std::string fileName);
    
    /// Support structure for a token-value pair
    template <typename T>
    struct InputTokenPair
    {
        // The parameter name
        std::string token;
        // The parameter value
        T tokenValue;
    };
    
    /// Parse double input parameters
    //template <typename T>
    //InputTokenPair<double>
    double parseDouble(std::string currentLine);
    
    /// Parse integer input parameters
    int parseInteger(std::string currentLine);
   
    /// Main file parser
    void parseInputFile();
};

#endif /* INPUTS_H */
