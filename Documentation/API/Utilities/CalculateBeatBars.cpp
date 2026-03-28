#include <iostream>

#include "RhythmGameUtilities/Utilities.hpp"

using namespace RhythmGameUtilities;

auto main() -> int
{
    const int resolution = 192;

    std::vector<Tempo> tempoChanges = {
        {0, 88000},      {3840, 112000},  {9984, 89600},  {22272, 112000},
        {33792, 111500}, {34560, 112000}, {42240, 111980}};

    auto beatBars = CalculateBeatBars(tempoChanges, resolution, true);

    std::cout << size(beatBars) << std::endl; // 440

    return 0;
}
