#include <iostream>

#include "RhythmGameUtilities/File.hpp"
#include "RhythmGameUtilities/Parsers/Chart.hpp"

using namespace RhythmGameUtilities;

auto main() -> int
{
    auto contents = ReadStringFromFile("./song.chart");

    auto resolution = ReadResolutionFromChartData(contents.c_str());

    std::cout << resolution << std::endl;

    return 0;
}
