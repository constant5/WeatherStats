#include "datetime.h"
#include <chrono>
#include <sstream>
#include <string>

using time_point = std::chrono::time_point<std::chrono::system_clock>;

void DateTime::datefromstring(std::string date, const char* fmt) {
	std::stringstream ss(date);
	std::chrono::from_stream(ss, fmt, dt);
};

bool DateTime::operator <=(DateTime& r) {
	return dt <= r.get();
}

bool DateTime::operator >=(DateTime& r) {
	return dt >= r.get();
}

bool DateTime::operator >(DateTime& r) {
	return dt > r.get();
}

time_point DateTime::get() {
	return dt;
}

int DateTime::getYear() {
	auto dp = floor<std::chrono::days>(dt);
	std::chrono::year_month_day ymd{ dp };
	auto y = ymd.year();
	auto m = ymd.month();
	auto d = ymd.day();
	return (int)y;
};
int DateTime::getSeconds() {
	using namespace std::chrono;
	auto tpc = time_point_cast<seconds>(dt);
	auto seconds = tpc.time_since_epoch().count();
	return seconds;
};
std::string DateTime::getLiteral() {
	using namespace std::chrono;
	std::string literal;
	literal = std::format("{:%H:%M}", dt);
	return literal;
};

//time_point datefromstring(std::string date, const char * fmt){
//	time_point timepoint;
//	std::stringstream ss(date);
//	std::chrono::from_stream(ss, fmt, timepoint);
//	return (timepoint);
//};

//int getyear(time_point datetime) {
//	auto dp = floor<std::chrono::days>(datetime);
//	std::chrono::year_month_day ymd{ dp };
//	auto y = ymd.year();
//	auto m = ymd.month();
//	auto d = ymd.day();
//	return (int) y;
//};

//std::vector<float> getSeconds(std::vector<time_point> dt) {
//
//}
//
//std::vector<std::string> getDTLiterals(std::vector<time_point> dt) {
//	using namespace std::chrono;
//	std::string s;
//	std::vector<std::string> literals;
//	for (auto tp : dt) {
//		s = std::format("{:%H:%M}", tp);
//		literals.push_back(s);
//	}
//	return literals;
//}