#include "miscellaneous.h"

std::mutex Miscellaneous::UserOutputMutex;
std::mutex Miscellaneous::UserInputMutex;

Miscellaneous::Miscellaneous()
{

}

std::string Miscellaneous::Make5DigitString(std::string _input)
{
    while(_input.size() != 5) {
        _input.insert(0, 1, '0');
    }
    return _input;
}

std::string Miscellaneous::Make5DigitString(int val)
{
    if(val > 99999) return "";
    else return Make5DigitString(std::to_string(val));
}

int Miscellaneous::GetIntegerFromUser(std::string _message)
{
    UserInputMutex.lock();
    int input;
    std::cout << _message;
    std::cin >> input;
    std::cout << std::endl;
    UserInputMutex.unlock();
    return input;
}

void Miscellaneous::PrintToScreen(std::string _message)
{
    UserOutputMutex.lock();
    std::cout << _message << std::endl;
    UserOutputMutex.unlock();
}
