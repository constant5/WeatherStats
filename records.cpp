#include "records.h"
#include "datetime.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <filesystem>
#include <sys/stat.h>
#include <chrono>
#include <map>
#include <boost/math/statistics/univariate_statistics.hpp>
#include <boost/math/statistics/linear_regression.hpp>

using namespace std;
using time_point = std::chrono::time_point<std::chrono::system_clock>;

std::vector<std::pair<std::string, int>> attributeValues{
	{"datetime", 0},
	{"Air_Temp", 1 }, 
	{"Barometric_Press", 2 },
	{"Dew_Point", 3},
	{"Relative_Humidity",4},
	{"Wind_Dir", 5},
	{"Wind_Gust", 6},
	{"Wind_Speed", 7}
};

std::map<std::string, int> attributeMap(attributeValues.begin(), attributeValues.end());


vector<string> WeatherRecords::getFiles(string startdate, string enddate) {
	const char * fmt = "%Y_%m_%d %T";
	DateTime starttime, stoptime;
	starttime.datefromstring(startdate, fmt);
	stoptime.datefromstring(enddate, fmt);


	int startyear = starttime.getYear();
	int stopyear = stoptime.getYear();



	int fileyear;
	vector <string> files = {
		"data/Environmental_Data_Deep_Moor_2012.txt",
		"data/Environmental_Data_Deep_Moor_2013.txt",
		"data/Environmental_Data_Deep_Moor_2014.txt",
		"data/Environmental_Data_Deep_Moor_2015.txt" };

	vector <string> files_req;

	for (auto f : files) {
		fileyear = stoi(f.substr(f.size()-8,4));
		if (fileyear >= startyear && fileyear <= stopyear)
			files_req.push_back(f);
	}

	return (files_req);
}

	

void WeatherRecords::readWeatherFile(string weatherfile, string startdate, string enddate) {
	ifstream inFile;

	const char* fmt = "%Y_%m_%d %T";
	DateTime starttime, stoptime;
	starttime.datefromstring(startdate, fmt);
	stoptime.datefromstring(enddate, fmt);

	string str, s;
	int count = 0;

	vector<string> record;
	DateTime dt;
	
	inFile.open(weatherfile);
	if (inFile.fail())
		cout << endl << "File not found!" << endl;
	else {
		// throw away header
		getline(inFile, str);
		while (!inFile.eof()) {
			record.clear();
			getline(inFile, str);
			stringstream ss(str);
			while (getline(ss, s, '\t')) {
				//cout << s << ' ';
				record.push_back(s);
			}
			dt.datefromstring(record[0], fmt);
			if (dt >= starttime && dt <= stoptime)
				addRecord(dt, record);
			else if (dt > stoptime)
				break;
		}
	}
}

void WeatherRecords::loadWeatherData(std::string start, std::string end) {
	auto files = getFiles(start, end);
	for (auto f : files)
		readWeatherFile(f, start, end);
}

void WeatherRecords::addRecord(DateTime dt, std::vector<string> record) {
	datetime.push_back(dt);
	Air_Temp.push_back(stof(record[1]));
	Barometric_Press.push_back(stof(record[2]));
	Dew_Point.push_back(stof(record[3]));
	Relative_Humidity.push_back(stof(record[4]));
	Wind_Dir.push_back(stof(record[5]));
	Wind_Gust.push_back(stof(record[6]));
	Wind_Speed.push_back(stof(record[7]));
}

std::vector<float> WeatherRecords::getAttribute(std::string attribute) {
	switch (attributeMap[attribute]) {
	case 0:
		break;
	case 1:
		return Air_Temp;
	case 2:
		return Barometric_Press;
	case 3:
		return Dew_Point;
	case 4:
		return Relative_Humidity;
	case 5:
		return Wind_Dir;
	case 6:
		return Wind_Gust;
	case 7:
		return Wind_Speed;
	}
}

std::vector<DateTime> WeatherRecords::getDateTime() {
	return datetime;
}

std::vector<float> WeatherRecords::getSeconds() {
	std::vector<float> sec_vec;

	for (auto dt : datetime)
		sec_vec.push_back(dt.getSeconds());
		return sec_vec;
}

std::vector<std::string> WeatherRecords::getDTLiterals() {
	std::vector<std::string> lit_vec;
	for (auto dt : datetime)
		lit_vec.push_back(dt.getLiteral());
	return lit_vec;
}

float WeatherRecords::getMean(std::string attribute) {
	auto r = getAttribute(attribute);
	return boost::math::statistics::mean(r);
}

void WeatherRecords::getSlope(std::string attribute, float coeff[]) {
	using boost::math::statistics::simple_ordinary_least_squares;
	auto r = getAttribute(attribute);
	auto x_vec = getSeconds();
	auto [c0, c1] = simple_ordinary_least_squares(x_vec, r);
	coeff[0] = c0;
	coeff[1] = c1;
}