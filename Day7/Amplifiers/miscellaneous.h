#ifndef MISCELLANEOUS_H
#define MISCELLANEOUS_H

#include <string>
#include <iostream>
#include <mutex>

class Miscellaneous
{
public:
    Miscellaneous();
    static std::string Make5DigitString(std::string _input);
    static std::string Make5DigitString(int val);
    static int GetIntegerFromUser(std::string _message);
    static void PrintToScreen(std::string _message);
private:
    static std::mutex UserInputMutex;
    static std::mutex UserOutputMutex;
};

#endif // MISCELLANEOUS_H
