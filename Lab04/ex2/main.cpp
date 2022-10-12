#include <iostream>
#include <cstdio>
#include "DayFunction.hpp"

DayInfo day1, day2;
using std::cout;

int main() {
    day1.day = day1.MONDAY;
    day2.day = day2.SUNDAY;
    day1.weather = day1.SUNNY;
    day2.weather = day2.SUNNY;

    cout << "Can day1, day2 travel? " << canTravel(day1) << " " << canTravel(day2) << std::endl; 
}