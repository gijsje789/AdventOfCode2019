#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <limits>

#define WIDTH 25
#define HEIGHT 6

int main()
{
    std::ifstream File("../puzzle_input.txt", std::ios::binary);
    std::ofstream OutFile("../output_image.txt", std::ios::out);
    std::vector<char> input(std::istreambuf_iterator<char>(File), {});

    std::string finalImage = "";

    std::string layer = "";
    std::vector<std::string> layers;
    int i = 0;
    int nrOfZeroes = 0;
    int nrOfOnes = 0;
    int nrOfTwos = 0;
    int minZeroes = std::numeric_limits<int>::max();
    int Ones = 0;
    int Twos = 0;

    for(char &val : input) {
        if(val == '0') nrOfZeroes++;
        else if (val == '1') nrOfOnes++;
        else if (val == '2') nrOfTwos++;

        layer.append(1, val);
        i++;
        if(i == (WIDTH*HEIGHT)) {
            layers.push_back(layer);
            std::cout << "Layer " << layers.size() << ": " << layer << std::endl;
            if(nrOfZeroes < minZeroes) {
                minZeroes = nrOfZeroes;
                Ones = nrOfOnes;
                Twos = nrOfTwos;
            }
            i = 0;
            nrOfZeroes = 0;
            nrOfOnes = 0;
            nrOfTwos = 0;
            layer.clear();
        }
    }

    for(i = 0; i < static_cast<int>(layers.front().size()); i++) {
        for(auto &str : layers) {
            if(str.at(i) == '0' || str.at(i) == '1') {
                finalImage.append(1, str.at(i));
                break;
            }
        }
    }

    std::cout << "Final image: " << std::endl;
    OutFile << "P3 25 6 1" << std::endl;
    i = 0;
    for(auto &chr : finalImage) {
        std::cout << chr;
        OutFile << chr << " " << chr << " " << chr << " ";
        i++;
        if(i == WIDTH) {
            std::cout << std::endl;
            OutFile << std::endl;
            i = 0;
        }
    }
    std::cout << "Layer of fewest zeroes, 1s*2s = " << Ones*Twos << std::endl;

    return 0;
}
