import RhythmGameUtilities from '@rhythm-game-utilities/core';

const delta = 50;

const notes = [
  { id: 1, position: 768 },
  { id: 2, position: 960 },
  { id: 3, position: 1152 },
  { id: 4, position: 1536 },
  { id: 5, position: 1728 },
  { id: 6, position: 1920 },
  { id: 7, position: 2304 },
  { id: 8, position: 2496 },
  { id: 9, position: 2688 },
  { id: 10, position: 3072 },
  { id: 11, position: 3264 }
];

const foundNotes = RhythmGameUtilities.FindNotesNearGivenTick(notes, 750, delta);

if (foundNotes?.length > 0) {
  console.log(foundNotes[0].position); // 768
}
