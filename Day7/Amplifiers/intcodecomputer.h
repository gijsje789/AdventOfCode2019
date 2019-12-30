#ifndef INTCODECOMPUTER_H
#define INTCODECOMPUTER_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <thread>
#include <chrono>

#include "miscellaneous.h"

class IntcodeComputer
{
public:
    IntcodeComputer(std::string _name);
    IntcodeComputer(std::string _name, std::vector<int>_intCodes);
    virtual ~IntcodeComputer();
    bool ReadIntCodesFromFile(std::string _file);
    void StartProgram(void);
    void WaitForProgramFinished(void);
    std::vector<int> GetIntcode(void);
    void SetIntcode(std::vector<int> _intCodes);

protected:
    std::string Name;
    bool OutputReady;

    virtual int GetInput(void);
    virtual void SetOutput(int val);

private:
    std::vector<int> IntCodes;
    size_t CurrentInstruction = 0;
    std::thread Program;

    void IntcodeProgram(void);
    int ExecuteCurrentInstruction(void);
    bool IsParameterInPositionMode(char ParamMode);
};

#endif // INTCODECOMPUTER_H
