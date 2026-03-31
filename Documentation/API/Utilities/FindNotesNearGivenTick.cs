using System;
using RhythmGameUtilities;

var notes = new Note[]
{
    new() { Position = 768 }, new() { Position = 960 }, new() { Position = 1152 }, new() { Position = 1536 },
    new() { Position = 1728 }, new() { Position = 1920 }, new() { Position = 2304 }, new() { Position = 2496 },
    new() { Position = 2688 }, new() { Position = 3072 }, new() { Position = 3264 }
};

var foundNotes = Utilities.FindNotesNearGivenTick(notes, 750);

if (foundNotes?.Length > 0)
{
    Console.Write(foundNotes[0].Position); // 768
}
