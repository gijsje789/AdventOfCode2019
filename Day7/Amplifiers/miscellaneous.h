#ifndef MISCELLANEOUS_H
#define MISCELLANEOUS_H

#include <string>

class Miscellaneous
{
public:
    Miscellaneous();
    static std::string Make5DigitString(std::string _input);
    static std::string Make5DigitString(int val);
};

#endif // MISCELLANEOUS_H
