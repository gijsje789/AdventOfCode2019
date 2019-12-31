#include <iostream>
#include <vector>
#include <fstream>

#include "miscellaneous.h"
#include "intcodecomputer.h"

int main()
{
    IntcodeComputer computer("MainComputer");

    if(computer.ReadIntCodesFromFile("../puzzle_input.txt")) {
        computer.StartProgram();
    }

    computer.WaitForProgramFinished();
    std::cout << "Program terminated." << std::endl;
    return 0;
}
