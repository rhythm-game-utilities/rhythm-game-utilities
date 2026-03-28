#include <iostream>

#include "RhythmGameUtilities/Utilities.hpp"

using namespace RhythmGameUtilities;

auto main() -> int
{
    const int bpm = 120;
    const float currentTime = 10;
    const float delta = 0.05f;

    auto isOnTheBeat = IsOnTheBeat(bpm, currentTime, delta);

    std::cout << (isOnTheBeat ? "Is on the beat!" : "Is not on the beat!")
              << std::endl; // "Is on the beat!"

    return 0;
}
