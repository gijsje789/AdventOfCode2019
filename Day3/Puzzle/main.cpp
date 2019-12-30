#include <iostream>
#include <fstream>
#include <vector>
#include <limits>

class Point {
public:
    Point(int _x, int _y)
        :x(_x), y(_y) {}
    void SetPoint(int _x, int _y) {x = _x; y = _y;}
    int GetDistance() {return abs(x)+abs(y);}
    std::string PrintString() {
        char temp[20];
        snprintf(temp, sizeof(temp), "(%d,%d)", x, y);
        return std::string(temp);
    }
    int x;
    int y;
};

class PointAndSteps {
public:
    PointAndSteps(Point _coord, int _steps)
        :Coord(_coord), Steps(_steps) {}

    int GetSteps() {return Steps;}
    Point Coord;
    int Steps;
};

bool IsLineHorizontal(Point p1, Point p2) {
    if(p1.x - p2.x != 0) return true;
    else return false;
}

bool IsOnHorizontalLine(Point t, Point p1, Point p2) {
    if(t.y == p1.y) {
        int small_x = p1.x < p2.x ? p1.x : p2.x;
        int large_x = p1.x > p2.x ? p1.x : p2.x;
        if(t.x > small_x && t.x < large_x) return true;
    }
    return false;
}

bool IsOnVerticalLine(Point t, Point p1, Point p2) {
    if(t.x == p1.x) {
        int small_y = p1.y < p2.y ? p1.y : p2.y;
        int large_y = p1.y > p2.y ? p1.y : p2.y;
        if(t.y > small_y && t.y < large_y) return true;
    }
    return false;
}

int NumberOfStepsToPoint(Point start, Point end) {
    return (abs(end.x-start.x) + abs(end.y-start.y));
}

int main()
{
    std::fstream File;
    std::string line;
    std::string element;
    std::vector<Point> wire[2];
    std::vector<PointAndSteps> intersection;
    wire[0].push_back(Point(0,0));
    wire[1].push_back(Point(0,0));

    int vecNr = 0;

    File.open("input.txt", std::ios::in);
    if(File.is_open()) {
        while(std::getline(File, line)) {
            std::cout << "Line: " << line << std::endl;
            for(char& c : line) {
                if(c == ',') {
                    std::cout << element << " ";
                    switch(element[0]) {
                    case 'R':
                        wire[vecNr].push_back(Point(wire[vecNr].back().x+std::stoi(element.substr(1,element.size()-1)), wire[vecNr].back().y));
                        break;

                    case 'L':
                        wire[vecNr].push_back(Point(wire[vecNr].back().x-std::stoi(element.substr(1,element.size()-1)), wire[vecNr].back().y));
                        break;

                    case 'U':
                        wire[vecNr].push_back(Point(wire[vecNr].back().x, wire[vecNr].back().y+std::stoi(element.substr(1,element.size()-1))));
                        break;

                    case 'D':
                        wire[vecNr].push_back(Point(wire[vecNr].back().x, wire[vecNr].back().y-std::stoi(element.substr(1,element.size()-1))));
                        break;
                    }
                    element.clear();
                    std::cout << "(" << wire[vecNr].back().x << "," << wire[vecNr].back().y << ")" <<  std::endl;
                } else {
                    element.append(1, c);
                }
            }
            element.clear();
            vecNr++;
        }
        int min_steps_wire0 = 0;
        int min_steps_wire1 = 0;
        int steps_0 = 0;
        int steps_1 = 0;
        for(size_t i = 0; i < wire[0].size()-1; i++) {
            min_steps_wire1 = 0;
            for(size_t j = 0; j < wire[1].size()-1; j++) {
                if(IsLineHorizontal(wire[0].at(i), wire[0].at(i+1))) {
                    if(!IsLineHorizontal(wire[1].at(j), wire[1].at(j+1))) {
                        Point top = wire[1].at(j).y > wire[1].at(j+1).y ? wire[1].at(j) : wire[1].at(j+1);
                        Point bottom = wire[1].at(j).y < wire[1].at(j+1).y ? wire[1].at(j) : wire[1].at(j+1);
                        for(int y = bottom.y; y <= top.y; y++) {
                            if(IsOnHorizontalLine(Point(wire[1].at(j).x, y), wire[0].at(i), wire[0].at(i+1))) {
                                steps_0 = NumberOfStepsToPoint(wire[0].at(i), Point(wire[1].at(j).x, y));
                                steps_1 = NumberOfStepsToPoint(wire[1].at(j), Point(wire[1].at(j).x, y));
                                //std::cout << "Point 0: " << wire[0].at(i).PrintString() << ", Point 1: " << wire[1].at(j).PrintString() << ", Target: " << Point(wire[1].at(j).x, y).PrintString();
                                //std::cout << ", Steps0: " << steps_0 << ", Steps1: " << steps_1 << std::endl;
                                intersection.push_back(PointAndSteps(Point(wire[1].at(j).x, y), min_steps_wire0+min_steps_wire1+steps_0+steps_1));
                            }
                        }
                    }
                } else { // !IsLineHorizontal wire[0].at(j)
                    if(IsLineHorizontal(wire[1].at(j), wire[1].at(j+1))) {
                        Point left = wire[1].at(j).x < wire[1].at(j+1).x ? wire[1].at(j) : wire[1].at(j+1);
                        Point right = wire[1].at(j).x > wire[1].at(j+1).x ? wire[1].at(j) : wire[1].at(j+1);
                        for(int x = left.x; x <= right.x; x++) {
                            if(IsOnVerticalLine(Point(x, wire[1].at(j).y), wire[0].at(i), wire[0].at(i+1))) {
                                steps_0 = NumberOfStepsToPoint(wire[0].at(i), Point(x, wire[1].at(j).y));
                                steps_1 = NumberOfStepsToPoint(wire[1].at(j), Point(x, wire[1].at(j).y));
                                //std::cout << "Point 0: " << wire[0].at(i).PrintString() << ", Point 1: " << wire[1].at(j).PrintString() << ", Target: " << Point(x, wire[1].at(j).y).PrintString();
                                //std::cout << ", Steps0: " << steps_0 << ", Steps1: " << steps_1 << std::endl;
                                intersection.push_back(PointAndSteps(Point(x, wire[1].at(j).y), min_steps_wire0+min_steps_wire1+steps_0+steps_1));
                            }
                        }
                    }
                }
                min_steps_wire1 += NumberOfStepsToPoint(wire[1].at(j), wire[1].at(j+1));
                //std::cout << "Point1_1: " << wire[1].at(j).PrintString() << " Point1_2: " << wire[1].at(j+1).PrintString() << ", Steps: " << min_steps_wire1 << std::endl;
            }
            min_steps_wire0 += NumberOfStepsToPoint(wire[0].at(i), wire[0].at(i+1));
            //std::cout << "Point0_1: " << wire[0].at(i).PrintString() << " Point0_2: " << wire[0].at(i+1).PrintString() << ", Steps: " << min_steps_wire0 << std::endl;
        }

        PointAndSteps smallest(Point(0,0), 0);
        int smallest_val = std::numeric_limits<int>::max();
        for(auto &element : intersection) {
            if(element.GetSteps() < smallest_val) {
                smallest_val = element.GetSteps();
                smallest.Coord.SetPoint(element.Coord.x, element.Coord.y);
                smallest.Steps = element.GetSteps();
            }
            std::cout << "(" << element.Coord.x << "," << element.Coord.y << "), distance: " << element.Coord.GetDistance() << ", Steps: " << element.GetSteps() << std::endl;
        }
        std::cout << "Smallest point (" << smallest.Coord.x << "," << smallest.Coord.y << "), distance: " << smallest.Coord.GetDistance() << ", Steps: " << smallest.GetSteps() << std::endl;
    }
    return 0;
}
