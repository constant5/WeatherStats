#include "plotting.h"
#include "datetime.h"
#include "records.h"
#include "matplotlibcpp.h"
#include <boost/range/adaptor/strided.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <boost/assign.hpp>
#include <algorithm>
#include <vector>


namespace plt = matplotlibcpp;

void plotAttribute(WeatherRecords myRecords, std::string attribute){

    auto data = myRecords.getAttribute(attribute);
    auto mean = myRecords.getMean(attribute);
    auto dt = myRecords.getDateTime();

    float cooef[2];
    myRecords.getSlope(attribute, cooef);

    auto literals = myRecords.getDTLiterals();
    auto seconds = myRecords.getSeconds();

    std::vector<float> fitted_line;
    for (auto s : seconds)
    fitted_line.push_back(cooef[0] + cooef[1] * s);

    int strides = floor(dt.size() / 10);
    auto s_literals = getStrides(literals, strides);
    auto s_seconds = getStrides(seconds, strides);


    plt::plot(seconds, data, { { "label",attribute } });
    plt::plot(seconds, fitted_line, { { "label","fit" } });
    plt::xticks(s_seconds, s_literals, { {"rotation","45"} });
    plt::title(attribute);
    plt::xlabel("seconds");
    plt::legend();
    plt::text(seconds[seconds.size() - (2 * strides)], mean, "c=" + std::to_string(cooef[1]*10000)+"e5");
    plt::show();
}

template <typename T>
std::vector<T> getStrides(std::vector<T> v, int strides) {
    using namespace boost::adaptors;
    using namespace boost::assign;

    std::vector<T> vec;
    boost::copy(
        v | strided(strides),
        std::back_inserter(vec));

    return vec;
}