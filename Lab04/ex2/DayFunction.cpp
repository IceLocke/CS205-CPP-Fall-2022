#include "DayInfo.hpp"

bool canTravel(DayInfo day) {
    if ((day.day == day.SATURDAY ||  day.day == day.SUNDAY) &&
        (day.weather == day.SUNNY))
        return true;
    else return false;
}