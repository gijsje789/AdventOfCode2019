#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>

class object {
public:
    object() {}
    object(std::string _name)
        :name(_name) {}
    std::string name;
    object* orbits = nullptr;
};

void ReadPuzzleInput(std::string file, std::vector<std::string> &vec) {
    std::fstream File;
    std::string line;

    File.open(file, std::ios::in);
    if(File.is_open()) {
        std::cout << "Reading orbital information." << std::endl;
        while(std::getline(File, line)) {
            vec.push_back(line);
        }
    }
}

int main()
{
    std::vector<std::string> input;
    std::map<std::string, object> orbital_data;
    ReadPuzzleInput("../puzzle_input.txt", input);

    for(auto &element : input) {
        std::string d_orbit = element.substr(0, element.find(')'));
        std::string object_name = element.substr(element.find(')')+1, element.size()-1);
        std::cout << "Object " << object_name << " orbits " << d_orbit << std::endl;
        if(!orbital_data.count(object_name)) {
            orbital_data[object_name] = object(object_name);
        }
        if(!orbital_data.count(d_orbit)) {
            orbital_data[d_orbit] = object(d_orbit);
        }
        orbital_data[object_name].orbits = &orbital_data[d_orbit];
    }

    int total_orbits = 0;
    object* subelement = nullptr;
    for(auto &element : orbital_data) {
        if(element.second.orbits != nullptr) {
            subelement = element.second.orbits;
            total_orbits++;
            if(subelement->orbits != nullptr) {
                do {
                    total_orbits++;
                    if(subelement->orbits != nullptr) subelement = subelement->orbits;
                }while(subelement->orbits != nullptr);
            }
        }
    }

    object* you_element = &orbital_data["YOU"];
    object* san_element = &orbital_data["SAN"];
    int you_orbits = 0;
    int san_orbits = 0;
    if(you_element->orbits != nullptr) {
        do {
            san_orbits = 0;
            san_element = &orbital_data["SAN"];
            if(san_element->orbits != nullptr) {
                do{

                    if(san_element->name.compare(you_element->name) == 0) {
                        // found mutual object.
                        // -1 because YOU/SAN does not count as an extra orbit step.
                        std::cout << "You orbits: " << you_orbits-1 << ", San orbits: " << san_orbits-1 << " Matching obj: " << san_element->name << "," << you_element->name << std::endl;
                    }
                    if(san_element->orbits != nullptr) san_element = san_element->orbits;
                    san_orbits++;
                }while(san_element->orbits != nullptr);
            }
            if(you_element->orbits != nullptr) you_element = you_element->orbits;
            you_orbits++;
        }while(you_element->orbits != nullptr);
    }
    std::cout << "Total orbits: " << total_orbits << std::endl;

    return 0;
}
