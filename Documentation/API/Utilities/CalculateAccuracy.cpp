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

    auto accuracy =
        CalculateAccuracy(note->Position, currentPosition, positionDelta);

    std::cout << ToString(accuracy) << std::endl; // Good

    return 0;
}
