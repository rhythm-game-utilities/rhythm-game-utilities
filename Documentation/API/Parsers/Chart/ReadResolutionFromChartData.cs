using System;
using System.IO;
using RhythmGameUtilities;

var contents = File.ReadAllText("./tests/Mocks/song.chart");

var resolution = Chart.ReadResolutionFromChartData(contents);

Console.WriteLine(resolution); // 192
