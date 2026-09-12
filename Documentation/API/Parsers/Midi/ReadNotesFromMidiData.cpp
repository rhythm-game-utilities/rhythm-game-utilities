#include <iostream>

#include "RhythmGameUtilities/File.hpp"
#include "RhythmGameUtilities/Parsers/Midi.hpp"

using namespace RhythmGameUtilities;

auto main() -> int
{
    auto bytes = ReadBytesFromFile("./tests/Mocks/song.mid");

    auto notes = ReadNotesFromMidiData(bytes);

    for (const auto &note : notes)
    {
        std::cout << note.Position << " " << note.HandPosition << std::endl;
    }

    return 0;
}
