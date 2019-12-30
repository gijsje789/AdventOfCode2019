#ifndef INTCODECOMPUTER_H
#define INTCODECOMPUTER_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <thread>

#include "miscellaneous.h"

class IntcodeComputer
{
public:
    IntcodeComputer(void);
    IntcodeComputer(std::vector<int>_intCodes);
    bool ReadIntCodesFromFile(std::string _file);
    void StartProgram(void);
    void WaitForProgramFinished();
private:
    std::vector<int> IntCodes;
    size_t CurrentInstruction = 0;
    std::thread Program;

    void IntcodeProgram(void);
    int ExecuteCurrentInstruction(void);
    bool IsParameterInPositionMode(char ParamMode);
};

#endif // INTCODECOMPUTER_H
