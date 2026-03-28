#include <iostream>

#include "RhythmGameUtilities/File.hpp"
#include "RhythmGameUtilities/Parsers/Chart.hpp"

using namespace RhythmGameUtilities;

auto main() -> int
{
    auto contents = ReadStringFromFile("./song.chart");

    auto timeSignatureChanges =
        ReadTimeSignatureChangesFromChartData(contents.c_str());

    std::cout << size(timeSignatureChanges) << std::endl; // 4

    return 0;
}
