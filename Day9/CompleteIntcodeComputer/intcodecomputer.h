#ifndef INTCODECOMPUTER_H
#define INTCODECOMPUTER_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <thread>
#include <chrono>

#include "miscellaneous.h"

#define PARAM1 2
#define PARAM2 1
#define PARAM3 0

class IntcodeComputer
{
public:
    IntcodeComputer(std::string _name);
    IntcodeComputer(std::string _name, std::vector<int64_t>_intCodes);
    virtual ~IntcodeComputer();
    bool ReadIntCodesFromFile(std::string _file);
    void StartProgram(void);
    void WaitForProgramFinished(void);
    std::vector<int64_t> GetIntcode(void);
    void SetIntcode(std::vector<int64_t> _intCodes);
    void ResetProgram(void);

protected:
    std::string Name;

    virtual int64_t GetInput(void);
    virtual void SetOutput(int64_t val);

private:
    std::vector<int64_t> IntCodes;
    size_t CurrentInstruction = 0;
    std::thread Program;
    int64_t RelativeBase = 0;

    void IntcodeProgram(void);
    int ExecuteCurrentInstruction(void);
    bool IsParameterInPositionMode(char ParamMode);
    bool IsParameterInImmediateMode(char ParamMode);
    bool IsParameterInRelativeMode(char ParamMode);
    int64_t* GetParam(int Param, char ParamMode);
    void FillProgramUntill(size_t index);
};

#endif // INTCODECOMPUTER_H
