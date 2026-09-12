using System;
using System.IO;
using RhythmGameUtilities;

var bytes = File.ReadAllBytes("./Tests/mocks/song.mid");

var tempoChanges = Midi.ReadTempoChangesFromMidiData(bytes);

Console.WriteLine(tempoChanges.Length); // 7
