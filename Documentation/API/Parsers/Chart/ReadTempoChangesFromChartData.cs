using System;
using System.IO;
using RhythmGameUtilities;

var contents = File.ReadAllText("./Tests/mocks/song.chart");

var tempoChanges = Chart.ReadTempoChangesFromChartData(contents);

Console.WriteLine(tempoChanges.Length); // 7
