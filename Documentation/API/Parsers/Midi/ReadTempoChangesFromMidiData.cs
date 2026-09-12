using System;
using System.IO;
using RhythmGameUtilities;

var bytes = File.ReadAllBytes("./tests/Mocks/song.mid");

var tempoChanges = Midi.ReadTempoChangesFromMidiData(bytes);

Console.WriteLine(tempoChanges.Length); // 1
