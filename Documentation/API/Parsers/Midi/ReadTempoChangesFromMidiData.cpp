#include <iostream>

#include "RhythmGameUtilities/File.hpp"
#include "RhythmGameUtilities/Parsers/Midi.hpp"

using namespace RhythmGameUtilities;

auto main() -> int
{
    auto bytes = ReadBytesFromFile("./song.mid");

    auto tempoChanges = ReadTempoChangesFromMidiData(bytes);

    std::cout << size(tempoChanges) << std::endl; // 7

    return 0;
}
