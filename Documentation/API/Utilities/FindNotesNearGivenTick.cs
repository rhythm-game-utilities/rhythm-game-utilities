using System;
using RhythmGameUtilities;

var notes = new Note[]
{
    new() { ID = 1, Position = 768 }, new() { ID = 2, Position = 960 },
    new() { ID = 3, Position = 1152 }, new() { ID = 4, Position = 1536 },
    new() { ID = 5, Position = 1728 }, new() { ID = 6,  Position = 1920 },
    new() { ID = 7, Position = 2304 }, new() { ID = 8, Position = 2496 },
    new() { ID = 9, Position = 2688 }, new() { ID = 10, Position = 3072 },
    new() { ID = 11, Position = 3264 }
};

var foundNotes = Utilities.FindNotesNearGivenTick(notes, 750);

if (foundNotes?.Length > 0)
{
    Console.Write(foundNotes[0].Position); // 768
}
