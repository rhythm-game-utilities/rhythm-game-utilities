using System;
using System.IO;
using RhythmGameUtilities;

var bytes = File.ReadAllBytes("./tests/Mocks/song.mid");

var notes = Midi.ReadNotesFromMidiData(bytes);

foreach (var note in notes)
{

    Console.WriteLine(note.Position + " " + note.HandPosition);

}
