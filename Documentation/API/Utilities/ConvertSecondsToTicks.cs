using System;
using RhythmGameUtilities;

const int seconds = 5;
const int resolution = 192;

var tempoChanges = new Tempo[]
{
    new() { Position = 0, BPM = 88000 }, new() { Position = 3840, BPM = 112000 },
    new() { Position = 9984, BPM = 89600 }, new() { Position = 22272, BPM = 112000 },
    new() { Position = 33792, BPM = 111500 }, new() { Position = 34560, BPM = 112000 },
    new() { Position = 42240, BPM = 111980 }
};

var ticks = Utilities.ConvertSecondsToTicks(seconds, resolution, tempoChanges);

Console.WriteLine(ticks); // 1408
