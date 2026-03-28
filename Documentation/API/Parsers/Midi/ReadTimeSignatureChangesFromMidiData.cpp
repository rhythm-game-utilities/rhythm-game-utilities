#include <iostream>

#include "RhythmGameUtilities/File.hpp"
#include "RhythmGameUtilities/Parsers/Midi.hpp"

using namespace RhythmGameUtilities;

auto main() -> int
{
    auto bytes = ReadBytesFromFile("./song.mid");

    auto timeSignatureChanges = ReadTimeSignatureChangesFromMidiData(bytes);

    std::cout << size(timeSignatureChanges) << std::endl; // 4

    return 0;
}
