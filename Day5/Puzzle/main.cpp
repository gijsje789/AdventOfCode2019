#include <iostream>
#include <vector>
#include <fstream>

std::string MakeInstruction5Digits(std::string _input) {
    while(_input.size() != 5) {
        _input.insert(0, 1, '0');
    }
    return _input;
}

int main()
{
    std::fstream File;
    std::string line;
    bool endProgram = false;
    size_t nrOfValues = 0;

    int param_1; // first after op_code etc.
    int param_2; // second after op_code etc.
    int param_3; // where to write to.
    int op_code;

    std::vector<int> input;

    int ID;
    std::cout << "TEST diagnostics program." << std::endl;

    File.open("input.txt", std::ios::in);
    if(File.is_open()) {
        std::cout << "File opened. Reading instructions." << std::endl;
        while(std::getline(File, line, ',')) {
        input.push_back(std::stoi(line));
        }
        line.clear();

        std::cout << "Instructions read successfully. Executing instructions." << std::endl;
        for(size_t index = 0; index < input.size(); index+=nrOfValues) {
            line = MakeInstruction5Digits(std::to_string(input[index]));

            op_code = std::stoi(line.substr(3, 2));
            switch(op_code) {
            case 1:
                param_1 = (line[2] - '0') == 0 ? input[static_cast<size_t>(input[index+1])] : input[index+1]; // position mode : immediate mode
                param_2 = (line[1] - '0') == 0 ? input[static_cast<size_t>(input[index+2])] : input[index+2]; // position mode : immediate mode
                param_3 = (line[0] - '0') == 0 ? input[index+3] : input[index+3];        // position mode : position mode
                input[static_cast<size_t>(param_3)] = param_1 + param_2;
                nrOfValues = 4;
                break;

            case 2:
                param_1 = (line[2] - '0') == 0 ? input[static_cast<size_t>(input[index+1])] : input[index+1]; // position mode : immediate mode
                param_2 = (line[1] - '0') == 0 ? input[static_cast<size_t>(input[index+2])] : input[index+2]; // position mode : immediate mode
                param_3 = (line[0] - '0') == 0 ? input[index+3] : input[index+3];        // position mode : position mode
                input[static_cast<size_t>(param_3)] = param_1 * param_2;
                nrOfValues = 4;
                break;

            case 3:
                std::cout << "Please provide the system's ID: ";
                std::cin >> ID;
                param_1 = ID;
                param_3 = (line[0] - '0') == 0 ? input[index+1] : input[index+1];        // position mode : position mode
                input[static_cast<size_t>(param_3)] = param_1;
                nrOfValues = 2;
                break;

            case 4:
                param_1 = (line[2] - '0') == 0 ? input[static_cast<size_t>(input[index+1])] : input[index+1]; // position mode : immediate mode
                std::cout << param_1 << std::endl;
                nrOfValues = 2;
                break;

            case 5:
                param_1 = (line[2] - '0') == 0 ? input[static_cast<size_t>(input[index+1])] : input[index+1]; // position mode : immediate mode
                param_2 = (line[1] - '0') == 0 ? input[static_cast<size_t>(input[index+2])] : input[index+2]; // position mode : immediate mode
                nrOfValues = 0;
                if(param_1 != 0) {
                    nrOfValues = 0;
                    index = static_cast<size_t>(param_2);
                } else {
                    nrOfValues = 3;
                }
                break;

            case 6:
                param_1 = (line[2] - '0') == 0 ? input[static_cast<size_t>(input[index+1])] : input[index+1]; // position mode : immediate mode
                param_2 = (line[1] - '0') == 0 ? input[static_cast<size_t>(input[index+2])] : input[index+2]; // position mode : immediate mode
                nrOfValues = 0;
                if(param_1 == 0) {
                    nrOfValues = 0;
                    index = static_cast<size_t>(param_2);
                } else {
                    nrOfValues = 3;
                }
                break;

            case 7:
                param_1 = (line[2] - '0') == 0 ? input[static_cast<size_t>(input[index+1])] : input[index+1]; // position mode : immediate mode
                param_2 = (line[1] - '0') == 0 ? input[static_cast<size_t>(input[index+2])] : input[index+2]; // position mode : immediate mode
                param_3 = (line[0] - '0') == 0 ? input[index+3] : input[index+3];        // position mode : position mode
                if(param_1 < param_2) input[static_cast<size_t>(param_3)] = 1;
                else input[static_cast<size_t>(param_3)] = 0;
                nrOfValues = 4;
                break;

            case 8:
                param_1 = (line[2] - '0') == 0 ? input[static_cast<size_t>(input[index+1])] : input[index+1]; // position mode : immediate mode
                param_2 = (line[1] - '0') == 0 ? input[static_cast<size_t>(input[index+2])] : input[index+2]; // position mode : immediate mode
                param_3 = (line[0] - '0') == 0 ? input[index+3] : input[index+3];        // position mode : position mode
                if(param_1 == param_2) input[static_cast<size_t>(param_3)] = 1;
                else input[static_cast<size_t>(param_3)] = 0;
                nrOfValues = 4;
                break;

            default:
                endProgram = true;
                break;
            }
            if(endProgram) break;
        }
        std::cout << "Program terminated." << std::endl;
    }
    return 0;
}
