#pragma once

#include <vector>
#include <string>
#include <chrono>
#include "datetime.h"


using time_point = std::chrono::time_point<std::chrono::system_clock>;

class WeatherRecords {
private:
	std::vector<DateTime> datetime;
	std::vector<float> Air_Temp;
	std::vector<float> Barometric_Press;
	std::vector<float> Dew_Point;
	std::vector<float> Relative_Humidity;
	std::vector<float> Wind_Dir;
	std::vector<float> Wind_Gust;
	std::vector<float> Wind_Speed;
public:
	void readWeatherFile(std::string, std::string, std::string);
	void loadWeatherData(std::string, std::string);
	void addRecord(DateTime, std::vector<std::string>);
	std::vector<float> getAttribute(std::string);
	std::vector<DateTime> getDateTime();
	std::vector<float> getSeconds();
	std::vector<std::string> getDTLiterals();
	float getMean(std::string);
	void getSlope(std::string,float arr[]);
	std::vector<std::string> getFiles(std::string startdate, std::string enddate);
};