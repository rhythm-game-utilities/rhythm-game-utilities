#include <cassert>
#include <iostream>

#include "RhythmGameUtilities/File.hpp"
#include "RhythmGameUtilities/Parsers/Midi.hpp"

using namespace RhythmGameUtilities;

void testReadResolutionFromMidiData()
{
    auto bytes = ReadBytesFromFile("./tests/Mocks/song.mid");

    auto resolution = ReadResolutionFromMidiData(bytes);

    assert(resolution == 480);

    std::cout << ".";
}

void testReadTempoChangesFromMidiData()
{
    auto bytes = ReadBytesFromFile("./tests/Mocks/song.mid");

    auto tempChanges = ReadTempoChangesFromMidiData(bytes);

    assert(size(tempChanges) == 1);
    assert(tempChanges[0].Position == 0);
    assert(tempChanges[0].BPM == 120000);

    std::cout << ".";
}
void testReadTimeSignatureChangesFromMidiData()
{
    auto bytes = ReadBytesFromFile("./tests/Mocks/song.mid");

    auto timeSignatureChanges = ReadTimeSignatureChangesFromMidiData(bytes);

    assert(size(timeSignatureChanges) == 1);

    assert(timeSignatureChanges[0].Position == 0);
    assert(timeSignatureChanges[0].Numerator == 4);
    assert(timeSignatureChanges[0].Denominator == 4);

    std::cout << ".";
}

void testReadNotesFromMidiData()
{
    auto bytes = ReadBytesFromFile("./tests/Mocks/song.mid");

    auto notes = ReadNotesFromMidiData(bytes);

    assert(size(notes) == 10);

    assert(notes[0].Position == 0);
    assert(notes[0].HandPosition == 48);

    assert(notes[1].Position == 480);
    assert(notes[1].HandPosition == 50);

    assert(notes[2].Position == 960);
    assert(notes[2].HandPosition == 52);

    assert(notes[3].Position == 1440);
    assert(notes[3].HandPosition == 54);

    assert(notes[4].Position == 1920);
    assert(notes[4].HandPosition == 56);

    assert(notes[5].Position == 2400);
    assert(notes[5].HandPosition == 48);

    assert(notes[6].Position == 2400);
    assert(notes[6].HandPosition == 50);

    assert(notes[7].Position == 2400);
    assert(notes[7].HandPosition == 52);

    assert(notes[8].Position == 2400);
    assert(notes[8].HandPosition == 54);

    assert(notes[9].Position == 2400);
    assert(notes[9].HandPosition == 56);

    std::cout << ".";
}

// ForEachMidiEvent (Parsers/Midi.hpp) reads a status byte unconditionally on
// every event and never handles MIDI running status — the standard
// convention where consecutive same-type events omit the repeated status
// byte, reusing the previous one. This is common in real-world MIDI files,
// not an edge case. This minimal 3-note file uses running status for its
// 2nd and 3rd NoteOn events; a correct parser returns 3 notes at ticks
// 0/480/960 with pitches 60/62/64. The current implementation desyncs on
// the first running-status event and does not.
void testReadNotesFromMidiDataWithRunningStatus()
{
    std::vector<uint8_t> bytes = {
        'M', 'T', 'h', 'd', 0, 0, 0, 6, 0, 0, 0, 1, 0x01, 0xE0, // header: format 0, 1 track, division 480
        'M', 'T', 'r', 'k', 0,    0,    0,    16,              // track chunk, 16 bytes
        0x00, 0x90, 60, 100,                                   // delta 0:   Note On ch0, note 60, vel 100
        0x83, 0x60, 62, 100,                                   // delta 480: running status, note 62, vel 100
        0x83, 0x60, 64, 100,                                   // delta 480: running status, note 64, vel 100
        0x00, 0xFF, 0x2F, 0x00                                 // delta 0:   End of Track
    };

    auto notes = ReadNotesFromMidiData(bytes);

    assert(size(notes) == 3);

    assert(notes[0].Position == 0);
    assert(notes[0].HandPosition == 60);

    assert(notes[1].Position == 480);
    assert(notes[1].HandPosition == 62);

    assert(notes[2].Position == 960);
    assert(notes[2].HandPosition == 64);

    std::cout << ".";
}

auto main() -> int
{
    testReadResolutionFromMidiData();
    testReadTempoChangesFromMidiData();
    testReadTimeSignatureChangesFromMidiData();
    testReadNotesFromMidiData();
    testReadNotesFromMidiDataWithRunningStatus();

    return 0;
}
