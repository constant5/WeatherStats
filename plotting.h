#pragma once
#include "records.h"
#include <vector>
void plotAttribute(WeatherRecords, std::string);

template <typename T>
std::vector<T> getStrides(std::vector<T>, int);
