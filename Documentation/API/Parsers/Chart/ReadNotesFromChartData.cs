using System;
using System.IO;
using RhythmGameUtilities;

var contents = File.ReadAllText("./tests/Mocks/song.chart");

var notes = Chart.ReadNotesFromChartData(contents, Difficulty.Expert);

foreach (var note in notes)
{

    Console.WriteLine(note.Position + " " + note.HandPosition);

}
