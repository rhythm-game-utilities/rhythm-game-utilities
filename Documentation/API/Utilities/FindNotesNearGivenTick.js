import RhythmGameUtilities from '@rhythm-game-utilities/core';

const delta = 50;

const notes = [
  { id: 1, position: 110 },
  { id: 2, position: 120 },
  { id: 3, position: 130 },
  { id: 4, position: 140 },
  { id: 5, position: 150 },
  { id: 6, position: 160 },
  { id: 7, position: 170 },
  { id: 8, position: 180 },
  { id: 9, position: 190 },
  { id: 10, position: 200 }
];

const foundNotes = RhythmGameUtilities.FindNotesNearGivenTick(notes, 160, delta);

console.log(foundNotes.length); // 5
