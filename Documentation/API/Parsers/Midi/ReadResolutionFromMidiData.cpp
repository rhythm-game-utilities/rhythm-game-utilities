#include <iostream>

#include "RhythmGameUtilities/File.hpp"
#include "RhythmGameUtilities/Parsers/Midi.hpp"

using namespace RhythmGameUtilities;

auto main() -> int
{
    auto bytes = ReadBytesFromFile("./song.mid");

    auto resolution = ReadResolutionFromMidiData(bytes);

    std::cout << resolution << std::endl;

    return 0;
}
