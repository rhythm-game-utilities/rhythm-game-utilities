#include <iostream>

#include "RhythmGameUtilities/Utilities.hpp"

using namespace RhythmGameUtilities;

auto main() -> int
{
    const int seconds = 2;
    const int resolution = 192;
    const int positionDelta = 50;

    std::vector<Tempo> tempoChanges = {{0, 120000}};

    auto note = new Note{1, 750};
    auto currentPosition =
        ConvertSecondsToTicks(seconds, resolution, tempoChanges);

    auto value =
        CalculateAccuracyRatio(note->Position, currentPosition, positionDelta);

    std::cout << value << std::endl; // 0.64

    return 0;
}
