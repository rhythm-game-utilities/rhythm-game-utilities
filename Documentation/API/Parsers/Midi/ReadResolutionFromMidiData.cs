using System;
using System.IO;
using RhythmGameUtilities;

var bytes = File.ReadAllBytes("./Tests/mocks/song.mid");

var resolution = Midi.ReadResolutionFromMidiData(bytes);

Console.WriteLine(resolution); // 192
