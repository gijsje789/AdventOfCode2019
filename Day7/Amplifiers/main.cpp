#include <iostream>
#include <vector>
#include <fstream>

#include "miscellaneous.h"
#include "intcodecomputer.h"

int main()
{
    IntcodeComputer comp;
    if(comp.ReadIntCodesFromFile("../input.txt")) {
        comp.StartProgram();
    }

    comp.WaitForProgramFinished();
    std::cout << "Program terminated." << std::endl;
    return 0;
}
