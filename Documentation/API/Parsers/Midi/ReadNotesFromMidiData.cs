using System;
using System.IO;
using RhythmGameUtilities;

var bytes = File.ReadAllBytes("./song.mid");

var notes = Midi.ReadNotesFromMidiData(bytes);

Console.WriteLine(notes.Length); // 8
