#include "intcodecomputer.h"

IntcodeComputer::IntcodeComputer()
{

}

IntcodeComputer::IntcodeComputer(std::vector<int> _intCodes)
    :IntCodes(_intCodes)
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
            IntCodes.push_back(std::stoi(Instruction));
        }
        return true;
    } else {
        std::cout << "Error: Cannot open file." << std::endl;
        return false;
    }
}

void IntcodeComputer::StartProgram()
{
    Program = std::thread(&IntcodeComputer::IntcodeProgram, this);
}

void IntcodeComputer::WaitForProgramFinished()
{
    if(Program.joinable()) {
        Program.join();
    }
}

void IntcodeComputer::IntcodeProgram()
{
    while(ExecuteCurrentInstruction()) {

    }
}

int IntcodeComputer::ExecuteCurrentInstruction()
{
    int param_1; // first after op_code etc.
    int param_2; // second after op_code etc.
    int param_3; // where to write to.

    int ID;
    int rval = 1;

    std::string instruction = Miscellaneous::Make5DigitString(IntCodes.at(CurrentInstruction));
    int op_code = std::stoi(instruction.substr(3, 2));

    switch(op_code) {
    case 1:
        param_1 = IsParameterInPositionMode(instruction[2]) ? IntCodes.at(static_cast<size_t>(IntCodes.at(CurrentInstruction+1))) : IntCodes.at(CurrentInstruction+1); // position mode : immediate mode
        param_2 = IsParameterInPositionMode(instruction[1]) ? IntCodes.at(static_cast<size_t>(IntCodes.at(CurrentInstruction+2))) : IntCodes.at(CurrentInstruction+2); // position mode : immediate mode
        param_3 = IsParameterInPositionMode(instruction[0]) ? IntCodes.at(CurrentInstruction+3) : IntCodes.at(CurrentInstruction+3);        // position mode : position mode
        IntCodes.at(static_cast<size_t>(param_3)) = param_1 + param_2;
        CurrentInstruction += 4;
        break;

    case 2:
        param_1 = IsParameterInPositionMode(instruction[2]) ? IntCodes.at(static_cast<size_t>(IntCodes.at(CurrentInstruction+1))) : IntCodes.at(CurrentInstruction+1); // position mode : immediate mode
        param_2 = IsParameterInPositionMode(instruction[1]) ? IntCodes.at(static_cast<size_t>(IntCodes.at(CurrentInstruction+2))) : IntCodes.at(CurrentInstruction+2); // position mode : immediate mode
        param_3 = IsParameterInPositionMode(instruction[0]) ? IntCodes.at(CurrentInstruction+3) : IntCodes.at(CurrentInstruction+3);        // position mode : position mode
        IntCodes.at(static_cast<size_t>(param_3)) = param_1 * param_2;
        CurrentInstruction += 4;
        break;

    case 3:
        std::cout << "Please provide the system's ID: ";
        std::cin >> ID;
        param_1 = ID;
        param_3 = IsParameterInPositionMode(instruction[0]) ? IntCodes.at(CurrentInstruction+1) : IntCodes.at(CurrentInstruction+1);        // position mode : position mode
        IntCodes.at(static_cast<size_t>(param_3)) = param_1;
        CurrentInstruction += 2;
        break;

    case 4:
        param_1 = IsParameterInPositionMode(instruction[2]) ? IntCodes.at(static_cast<size_t>(IntCodes.at(CurrentInstruction+1))) : IntCodes.at(CurrentInstruction+1); // position mode : immediate mode
        std::cout << param_1 << std::endl;
        CurrentInstruction += 2;
        break;

    case 5:
        param_1 = IsParameterInPositionMode(instruction[2]) ? IntCodes.at(static_cast<size_t>(IntCodes.at(CurrentInstruction+1))) : IntCodes.at(CurrentInstruction+1); // position mode : immediate mode
        param_2 = IsParameterInPositionMode(instruction[1]) ? IntCodes.at(static_cast<size_t>(IntCodes.at(CurrentInstruction+2))) : IntCodes.at(CurrentInstruction+2); // position mode : immediate mode
        if(param_1 != 0) {
            CurrentInstruction = static_cast<size_t>(param_2);
        } else {
            CurrentInstruction += 3;
        }
        break;

    case 6:
        param_1 = IsParameterInPositionMode(instruction[2]) ? IntCodes.at(static_cast<size_t>(IntCodes.at(CurrentInstruction+1))) : IntCodes.at(CurrentInstruction+1); // position mode : immediate mode
        param_2 = IsParameterInPositionMode(instruction[1]) ? IntCodes.at(static_cast<size_t>(IntCodes.at(CurrentInstruction+2))) : IntCodes.at(CurrentInstruction+2); // position mode : immediate mode
        if(param_1 == 0) {
            CurrentInstruction = static_cast<size_t>(param_2);
        } else {
            CurrentInstruction += 3;
        }
        break;

    case 7:
        param_1 = IsParameterInPositionMode(instruction[2]) ? IntCodes.at(static_cast<size_t>(IntCodes.at(CurrentInstruction+1))) : IntCodes.at(CurrentInstruction+1); // position mode : immediate mode
        param_2 = IsParameterInPositionMode(instruction[1]) ? IntCodes.at(static_cast<size_t>(IntCodes.at(CurrentInstruction+2))) : IntCodes.at(CurrentInstruction+2); // position mode : immediate mode
        param_3 = IsParameterInPositionMode(instruction[0]) ? IntCodes.at(CurrentInstruction+3) : IntCodes.at(CurrentInstruction+3);        // position mode : position mode
        if(param_1 < param_2) IntCodes.at(static_cast<size_t>(param_3)) = 1;
        else IntCodes.at(static_cast<size_t>(param_3)) = 0;
        CurrentInstruction += 4;
        break;

    case 8:
        param_1 = IsParameterInPositionMode(instruction[2]) ? IntCodes.at(static_cast<size_t>(IntCodes.at(CurrentInstruction+1))) : IntCodes.at(CurrentInstruction+1); // position mode : immediate mode
        param_2 = IsParameterInPositionMode(instruction[1]) ? IntCodes.at(static_cast<size_t>(IntCodes.at(CurrentInstruction+2))) : IntCodes.at(CurrentInstruction+2); // position mode : immediate mode
        param_3 = IsParameterInPositionMode(instruction[0]) ? IntCodes.at(CurrentInstruction+3) : IntCodes.at(CurrentInstruction+3);        // position mode : position mode
        if(param_1 == param_2) IntCodes.at(static_cast<size_t>(param_3)) = 1;
        else IntCodes.at(static_cast<size_t>(param_3)) = 0;
        CurrentInstruction += 4;
        break;

    default:
        rval = 0;
        break;
    }
    return rval;
}

bool IntcodeComputer::IsParameterInPositionMode(char ParamMode)
{
    return (ParamMode - '0' == 0);
}
