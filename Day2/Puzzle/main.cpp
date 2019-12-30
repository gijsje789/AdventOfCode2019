#include <iostream>
#include <vector>
#include <fstream>

#define GOAL 19690720

int main()
{
    std::vector<int> input;
    std::vector<int> data;
    std::fstream File;
    std::string line;
    bool endProgram = false;
    bool pairFound = false;
    int noun = 0;
    int verb = 0;
    File.open("intcodes.txt", std::ios::in);
    if(File.is_open()) {
        while(std::getline(File, line, ',')) {
        input.push_back(std::stoi(line));
        }
    }
    data = input;
    for(noun = 0; noun < 100; noun++) {
        for(verb = 0; verb < 100; verb++) {
            data = input; // reset data.
            data.at(1) = noun;
            data.at(2) = verb;
            endProgram = false;
            for(std::vector<int>::size_type index = 0; index < data.size(); index+=4) {
                switch(data[index]) {
                case 1:
                    data[static_cast<std::vector<int>::size_type>(data[index+3])] =
                            data[static_cast<std::vector<int>::size_type>(data[index+1])] + data[static_cast<std::vector<int>::size_type>(data[index+2])];
                    break;

                case 2:
                    data[static_cast<std::vector<int>::size_type>(data[index+3])] =
                            data[static_cast<std::vector<int>::size_type>(data[index+1])] * data[static_cast<std::vector<int>::size_type>(data[index+2])];
                    break;

                default:
                    endProgram = true;
                    break;
                }

                if(endProgram) break;
            }
            if(data.front() == GOAL) {
                pairFound = true;
                std::cout << "Noun: " << noun << ", Verb: " << verb << ", 100*noun+verb: " << (100*noun+verb) << std::endl;
                break;
            }
        }
        if(pairFound) break;
    }
    return 0;
}
