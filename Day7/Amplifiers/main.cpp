#include <iostream>
#include <vector>
#include <fstream>

#include "miscellaneous.h"
#include "amplifier.h"

std::string Make5Digit(std::string inp) {
    std::string rval = inp;
    while(rval.size() != 5) {
        rval.insert(0, 1, '0');
    }
    return rval;
}

bool IsPhaseSettingValid(int phase_setting) {
    std::string phases = std::to_string(phase_setting);
    phases = Make5Digit(phases);

    for(size_t i = 0; i < phases.size(); i++) {
        if(phases.at(i)-'0' < 5) return false;
        for(size_t j = 0; j < phases.size(); j++) {
            if(i != j) {
                if(phases.at(i) == phases.at(j)) {
                    return false;
                }
            }
        }
    }
    return true;
}

int main()
{
    Amplifier initAmp("Amplifier A", 0);
    initAmp.ReadIntCodesFromFile("../puzzle_input.txt");
    std::vector<int> IntCodes = initAmp.GetIntcode();
    int max_output = 0;

    for(int i = 56789; i <= 99999; i++) {
        if(!IsPhaseSettingValid(i)) continue;
        std::string phase = Make5Digit(std::to_string(i));
        std::vector<Amplifier*> amplifiers;

        amplifiers.push_back(new Amplifier("E", phase[4]-'0', IntCodes));
        amplifiers.push_back(new Amplifier("D", phase[3]-'0', IntCodes, amplifiers.back()));
        amplifiers.push_back(new Amplifier("C", phase[2]-'0', IntCodes, amplifiers.back()));
        amplifiers.push_back(new Amplifier("B", phase[1]-'0', IntCodes, amplifiers.back()));
        amplifiers.push_back(new Amplifier("A", phase[0]-'0', IntCodes, amplifiers.back()));
        amplifiers.front()->SetNextModule(amplifiers.back());

        for(Amplifier* amp : amplifiers) {
            amp->StartProgram();
        }

        amplifiers.back()->GiveInput(0);

        for(Amplifier* amp : amplifiers) {
            amp->WaitForProgramFinished();
        }

        max_output = amplifiers.front()->GetOutput() > max_output ? amplifiers.front()->GetOutput() : max_output;
        std::cout << "Phase: " << i << ", output: " << amplifiers.front()->GetOutput() << std::endl;

        for(Amplifier* amp : amplifiers) {
            delete amp;
        }
    }
    std::cout << "Program terminated. Max output: " << max_output << std::endl;
    return 0;
}
