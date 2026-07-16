#include <iostream>

#include "RhythmGameUtilities/Utilities.hpp"

using namespace RhythmGameUtilities;

auto main() -> int
{
    std::vector<Note> notes = {
        {1, 768, 0, 0},  {2, 960, 0, 0},   {3, 1152, 0, 0}, {4, 1536, 0, 0},
        {5, 1728, 0, 0}, {6, 1920, 0, 0},  {7, 2304, 0, 0}, {8, 2496, 0, 0},
        {9, 2688, 0, 0}, {10, 3072, 0, 0}, {11, 3264, 0, 0}};

    auto foundNotes = FindNotesNearGivenTick(notes, 750);

    if (size(foundNotes) > 0)
    {
        std::cout << foundNotes[0].Position << std::endl; // 768
    }

    return 0;
}
