using System;
using System.IO;
using RhythmGameUtilities;

var contents = File.ReadAllText("./Tests/mocks/song.chart");

var timeSignatureChanges = Chart.ReadTimeSignatureChangesFromChartData(contents);

Console.WriteLine(timeSignatureChanges.Length); // 4
