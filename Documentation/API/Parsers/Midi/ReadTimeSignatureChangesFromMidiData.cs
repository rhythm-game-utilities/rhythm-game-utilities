using System;
using System.IO;
using RhythmGameUtilities;

var bytes = File.ReadAllBytes("./tests/Mocks/song.mid");

var timeSignatureChanges = Midi.ReadTimeSignatureChangesFromMidiData(bytes);

Console.WriteLine(timeSignatureChanges.Length); // 1
