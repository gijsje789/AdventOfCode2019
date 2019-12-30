#ifndef AMPLIFIER_H
#define AMPLIFIER_H

#include "intcodecomputer.h"

class Amplifier : public IntcodeComputer
{
public:
    Amplifier(std::string _name, int _phase);
    Amplifier(std::string _name, int _phase, std::vector<int> _intCodes, Amplifier* _nextModule = nullptr);
    ~Amplifier();

    void GiveInput(int val);
    void SetNextModule(Amplifier* _nextModule);
    int GetOutput(void);
    void SetPhase(int _phase);
private:
    bool PhaseSet = false;
    int Phase;
    bool InputReady = false;
    int InputOutput = 0;
    Amplifier* NextModule = nullptr;

    int GetInput(void);
    void SetOutput(int val);
};

#endif // AMPLIFIER_H
