#include "miscellaneous.h"

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
