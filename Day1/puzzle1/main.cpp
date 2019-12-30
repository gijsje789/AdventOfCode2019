#include <iostream>
#include <fstream>
#include <math.h>

int CalculateFuelReq(int mass) {
    return floor(static_cast<double>((mass)/3.0))-2;
}

int main()
{
    std::fstream pFile;
    std::string line;
    int sum = 0;

    pFile.open("modules.txt", std::ios::in);
    if(pFile.is_open()) {
        while(std::getline(pFile, line)) {
            int module_mass = std::stoi(line);
            int module_fuel_req = CalculateFuelReq(module_mass);
            sum += module_fuel_req;

            do {
                module_fuel_req = CalculateFuelReq(module_fuel_req);
                module_fuel_req = module_fuel_req <= 0 ? 0 : module_fuel_req;
                sum += module_fuel_req;
                std::cout << module_fuel_req << std::endl;
            }while(module_fuel_req);
        }
    }
    std::cout << "Total fuel: " << sum << std::endl;

    return 0;
}
