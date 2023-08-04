// C++CodeClinic.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "records.h"
#include "plotting.h"
#include <string>

WeatherRecords myRecords;
void initialize();

int main()
{
    initialize();
    return (0);
}

void initialize() {
    std::string startdate = "2012_01_01 00:00:00";
    std::string enddate = "2012_01_31 00:00:00";
    myRecords.loadWeatherData(startdate, enddate);
    std::string attribute {"Barometric_Press" };
    plotAttribute(myRecords, attribute);
}

   
