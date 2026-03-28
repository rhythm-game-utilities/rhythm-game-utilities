#include <iostream>

#include "RhythmGameUtilities/Utilities.hpp"

using namespace RhythmGameUtilities;

auto main() -> int
{
    const int seconds = 2;
    const int resolution = 192;
    const int positionDelta = 50;

    std::vector<Tempo> tempoChanges = {{0, 120000}};

    auto note = new Note{750};
    auto currentPosition =
        ConvertSecondsToTicks(seconds, resolution, tempoChanges);

    auto timing =
        CalculateTiming(note->Position, currentPosition, positionDelta);

    std::cout << ToString(timing) << std::endl; // Hit

    return 0;
}
