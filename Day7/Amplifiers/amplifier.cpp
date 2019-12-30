#include "amplifier.h"

Amplifier::Amplifier(std::string _name, int _phase)
    : IntcodeComputer (_name), Phase(_phase)
{

}

Amplifier::Amplifier(std::string _name, int _phase, std::vector<int> _intCodes, Amplifier *_nextModule)
    : IntcodeComputer (_name, _intCodes), Phase(_phase), NextModule(_nextModule)
{

}

Amplifier::~Amplifier()
{

}

void Amplifier::GiveInput(int val)
{
    InputReady = true;
    InputOutput = val;
}

void Amplifier::SetNextModule(Amplifier *_nextModule)
{
    NextModule = _nextModule;
}

int Amplifier::GetOutput()
{
    return InputOutput;
}

void Amplifier::SetPhase(int _phase)
{
    Phase = _phase;
}

int Amplifier::GetInput()
{
    if(PhaseSet) {
        while(!InputReady) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        InputReady = false;
        return InputOutput;
    } else {
        PhaseSet = true;
        return Phase;
    }
}

void Amplifier::SetOutput(int val)
{
    InputOutput = val;
    if(NextModule == nullptr) IntcodeComputer::SetOutput(val);
    else NextModule->GiveInput(val);
}
