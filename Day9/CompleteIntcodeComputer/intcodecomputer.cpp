#include "intcodecomputer.h"

IntcodeComputer::IntcodeComputer(std::string _name)
    :Name(_name)
{

}

IntcodeComputer::IntcodeComputer(std::string _name, std::vector<int64_t> _intCodes)
    : Name(_name), IntCodes(_intCodes)
{

}

IntcodeComputer::~IntcodeComputer()
{

}

bool IntcodeComputer::ReadIntCodesFromFile(std::string _file)
{
    std::fstream File;
    std::string Instruction;

    File.open(_file, std::ios::in);
    if(File.is_open()) {
        std::cout << "File opened. Reading instructions." << std::endl;
        while(std::getline(File, Instruction, ',')) {
            IntCodes.push_back(std::stoll(Instruction));
        }
        return true;
    } else {
        std::cout << "Error: Cannot open file." << std::endl;
        return false;
    }
}

void IntcodeComputer::StartProgram(void)
{
    Program = std::thread(&IntcodeComputer::IntcodeProgram, this);
}

void IntcodeComputer::WaitForProgramFinished(void)
{
    if(Program.joinable()) {
        Program.join();
    }
}

std::vector<int64_t> IntcodeComputer::GetIntcode()
{
    return IntCodes;
}

void IntcodeComputer::SetIntcode(std::vector<int64_t> _intCodes)
{
    IntCodes = _intCodes;
}

void IntcodeComputer::ResetProgram()
{
    CurrentInstruction = 0;
}

void IntcodeComputer::IntcodeProgram(void)
{
    while(ExecuteCurrentInstruction()) {

    }
}

int IntcodeComputer::ExecuteCurrentInstruction(void)
{
    int rval = 1;

    std::string instruction = Miscellaneous::Make5DigitString(IntCodes.at(CurrentInstruction));
    int op_code = std::stoi(instruction.substr(3, 2));
    //std::cout << ", Cur: " << CurrentInstruction << ", RelBase: " << RelativeBase << ", Instruction output: ";
    switch(op_code) {
    case 1:
        *GetParam(3, instruction[PARAM3]) = *GetParam(1, instruction[PARAM1]) + *GetParam(2, instruction[PARAM2]);
        CurrentInstruction += 4;
        break;

    case 2:
        *GetParam(3, instruction[PARAM3]) = *GetParam(1, instruction[PARAM1]) * *GetParam(2, instruction[PARAM2]);
        CurrentInstruction += 4;
        break;

    case 3:
        *GetParam(1, instruction[PARAM1]) = GetInput();
        CurrentInstruction += 2;
        break;

    case 4:
        SetOutput(*GetParam(1, instruction[PARAM1]));
        CurrentInstruction += 2;
        break;

    case 5:
        if(*GetParam(1, instruction[PARAM1]) != 0) {
            CurrentInstruction = static_cast<size_t>(*GetParam(2, instruction[PARAM2]));
        } else {
            CurrentInstruction += 3;
        }
        break;

    case 6:
        if(*GetParam(1, instruction[PARAM1]) == 0) {
            CurrentInstruction = static_cast<size_t>(*GetParam(2, instruction[PARAM2]));
        } else {
            CurrentInstruction += 3;
        }
        break;

    case 7:
        if(*GetParam(1, instruction[PARAM1]) < *GetParam(2, instruction[PARAM2])) *GetParam(3, instruction[PARAM3]) = 1;
        else *GetParam(3, instruction[PARAM3]) = 0;
        CurrentInstruction += 4;
        break;

    case 8:
        if(*GetParam(1, instruction[PARAM1]) == *GetParam(2, instruction[PARAM2])) *GetParam(3, instruction[PARAM3]) = 1;
        else *GetParam(3, instruction[PARAM3]) = 0;
        CurrentInstruction += 4;
        break;

    case 9:
        RelativeBase += *GetParam(1, instruction[PARAM1]);
        CurrentInstruction += 2;
        break;

    default:
        rval = 0;
        break;
    }
    //std::cout << std::endl;
    return rval;
}

bool IntcodeComputer::IsParameterInPositionMode(char ParamMode)
{
    return (ParamMode == '0');
}

bool IntcodeComputer::IsParameterInImmediateMode(char ParamMode)
{
    return (ParamMode == '1');
}

bool IntcodeComputer::IsParameterInRelativeMode(char ParamMode)
{
    return (ParamMode == '2');
}

int64_t* IntcodeComputer::GetParam(int Param, char ParamMode)
{
    size_t param_pos;
    //if(Param == 3 && IsParameterInImmediateMode(ParamMode)) param_pos = static_cast<size_t>(IntCodes[CurrentInstruction+static_cast<size_t>(Param)]); // Force position mode on immediate param3
    /*else*/ if(IsParameterInPositionMode(ParamMode))           param_pos = static_cast<size_t>(IntCodes[CurrentInstruction+static_cast<size_t>(Param)]);
    else if (IsParameterInImmediateMode(ParamMode))         param_pos = CurrentInstruction+static_cast<size_t>(Param);
    else if (IsParameterInRelativeMode(ParamMode))          param_pos = static_cast<size_t>(RelativeBase + IntCodes[CurrentInstruction+static_cast<size_t>(Param)]);
    else return nullptr;

    if(param_pos > IntCodes.size()) FillProgramUntill(param_pos);
    //std::cout << " " << "P" << Param << ": " << IntCodes[param_pos];
    return &IntCodes[param_pos];
}

void IntcodeComputer::FillProgramUntill(size_t index)
{
    while(IntCodes.size()-1 != index) {
        IntCodes.push_back(0);
    }
}

int64_t IntcodeComputer::GetInput(void)
{
    return static_cast<int64_t>(Miscellaneous::GetIntegerFromUser("IntcodeComputer " + Name + " wants an integer: "));
}

void IntcodeComputer::SetOutput(int64_t val)
{
    Miscellaneous::PrintToScreen(std::to_string(val));
}


