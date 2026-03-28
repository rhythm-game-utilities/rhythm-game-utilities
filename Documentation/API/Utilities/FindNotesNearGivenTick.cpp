#include <iostream>

#include "RhythmGameUtilities/Utilities.hpp"

using namespace RhythmGameUtilities;

auto main() -> int
{
    std::vector<Note> notes = {{768, 0, 0},  {960, 0, 0},  {1152, 0, 0},
                               {1536, 0, 0}, {1728, 0, 0}, {1920, 0, 0},
                               {2304, 0, 0}, {2496, 0, 0}, {2688, 0, 0},
                               {3072, 0, 0}, {3264, 0, 0}};

    auto foundNotes = FindNotesNearGivenTick(notes, 750);

    if (size(foundNotes) > 0)
    {
        std::cout << foundNotes[0].Position << std::endl; // 768
    }

    return 0;
}
