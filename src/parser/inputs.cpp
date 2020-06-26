//
//  inputs.cpp
//  flowSolve
//
//  Created by Julian Toumey on 6/17/20.
//

#include "inputs.h"

Inputs::Inputs(std::string inputFileName_) : inputFileName(inputFileName_)
{
    // Verify our input file exists and exit if not
    bool fileFound = checkFileExistence(inputFileName);
    
    if (!fileFound)
    {
        exit (0);
    }
}

int Inputs::checkFileExistence(std::string fileName)
{
    // Open the file and test success
    std::ifstream inputStream;
    inputStream.open(fileName, std::ios::in);
    if (!inputStream)
    {
        std::cout << "ERROR: File " << fileName
        << " does not exist in the current working directory."
        << std::endl;
        
        return (false);
    }
    else
    {
        std::cout << "Input file " << fileName << " found successfully."
        << std::endl;
        
        return (true);
    }
}

double Inputs::parseDouble(std::string currentLine)
{
    // Bracket the double parameter. Assumes that there are no spaces
    // between the final char of the double and the ";" line terminator
    size_t dblStart = currentLine.find_last_of(" ") + 1;
    size_t dblEnd = currentLine.find(";");
    size_t dblWidth = dblEnd - dblStart;
    
    double extractedValue =
    std::stod(currentLine.substr(dblStart, dblWidth));
    
    return (extractedValue);
}

int Inputs::parseInteger(std::string currentLine)
{
    // Bracket the double parameter. Assumes that there are no spaces
    // between the final char of the double and the ";" line terminator
    size_t intStart = currentLine.find_last_of(" ") + 1;
    size_t intEnd = currentLine.find(";");
    size_t intWidth = intEnd - intStart;
    
    int extractedValue =
    std::stoi(currentLine.substr(intStart, intWidth));
    
    return (extractedValue);
}

void Inputs::parseInputFile()
{
    std::ifstream fileStream(inputFileName);
    std::string line;
    std::vector<std::string> inputKeysTemp = inputKeys;
    // Loop over file items
    int lineIdx = 0;
    while (std::getline(fileStream, line))
    {
        for (int ii = 0; ii != inputKeysTemp.size(); ++ii)
        {
            std::string currentKey = inputKeysTemp[ii];
            
            if (line.find(currentKey) != std::string::npos)
            {
                if (currentKey == "dimension")
                {
                    double dd = parseDouble(line);
                    simDimension = dd;
                    std::cout << "Simulation dimension is " << dd << "."
                    << std::endl;
                    inputKeysTemp.erase(inputKeysTemp.begin() + ii);
                }
                else if (currentKey == "x1Min")
                {
                    domainBbox.x1Min = parseDouble(line);
                    inputKeysTemp.erase(inputKeysTemp.begin() + ii);
                }
                else if (currentKey == "x1Max")
                {
                    domainBbox.x1Max = parseDouble(line);
                    inputKeysTemp.erase(inputKeysTemp.begin() + ii);
                }
                else if (currentKey == "x2Min")
                {
                    domainBbox.x2Min = parseDouble(line);
                    inputKeysTemp.erase(inputKeysTemp.begin() + ii);
                }
                else if (currentKey == "x2Max")
                {
                    domainBbox.x2Max = parseDouble(line);
                    inputKeysTemp.erase(inputKeysTemp.begin() + ii);
                }
                else if (currentKey == "x1Cells")
                {
                    x1Cells = parseInteger(line);
                    inputKeysTemp.erase(inputKeysTemp.begin() + ii);
                }
                else if (currentKey == "x2Cells")
                {
                    x2Cells = parseInteger(line);
                    // This is by convention the last parameter in the file.
                    // Thus, we don't pop the parameter from the temp input key
                    // list because this results in a memory error. Need a
                    // safer method.
                    // inputKeysTemp.erase(inputKeysTemp.begin() + ii);
                }
            }
        }
        ++lineIdx;
    }
    fileStream.close();
}
