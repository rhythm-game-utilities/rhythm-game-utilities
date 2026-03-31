using System;
using System.IO;
using RhythmGameUtilities;

var contents = File.ReadAllText("./song.chart");

var notes = Chart.ReadNotesFromChartData(contents, Difficulty.Expert);

Console.WriteLine(notes.Length); // 8
