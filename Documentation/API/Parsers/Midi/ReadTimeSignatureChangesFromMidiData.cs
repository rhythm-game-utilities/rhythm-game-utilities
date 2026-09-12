using System;
using System.IO;
using RhythmGameUtilities;

var bytes = File.ReadAllBytes("./Tests/mocks/song.mid");

var timeSignatureChanges = Midi.ReadTimeSignatureChangesFromMidiData(bytes);

Console.WriteLine(timeSignatureChanges.Length); // 1
