import RhythmGameUtilities from '@rhythm-game-utilities/core';

const tempoChanges = [
  { position: 0, bpm: 88000 },
  { position: 3840, bpm: 112000 },
  { position: 9984, bpm: 89600 },
  { position: 22272, bpm: 112000 },
  { position: 33792, bpm: 111500 },
  { position: 34560, bpm: 112000 },
  { position: 42240, bpm: 111980 }
];

const resolution = 192;

const beatBars = RhythmGameUtilities.CalculateBeatBars(tempoChanges, resolution, true);

console.log(beatBars.length); // 440
