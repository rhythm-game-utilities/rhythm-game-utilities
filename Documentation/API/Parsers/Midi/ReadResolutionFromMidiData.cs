using System;
using System.IO;
using RhythmGameUtilities;

var bytes = File.ReadAllBytes("./tests/Mocks/song.mid");

var resolution = Midi.ReadResolutionFromMidiData(bytes);

Console.WriteLine(resolution); // 480
