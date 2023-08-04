#pragma once
#include <string>
#include <chrono>

using time_point = std::chrono::time_point<std::chrono::system_clock>;


class DateTime {
private:
	time_point dt;
public:
	void datefromstring(std::string, const char*);
	int getYear();
	int getSeconds();
	std::string getLiteral();
	time_point get();

	bool operator <=(DateTime&);
	bool operator >=(DateTime&);
	bool operator >(DateTime&);
};


//std::vector<float> getSeconds(std::vector<time_point>);
//std::vector<std::string> getDTLiterals(std::vector<time_point>);