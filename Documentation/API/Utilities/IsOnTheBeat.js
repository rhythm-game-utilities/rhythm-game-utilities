import RhythmGameUtilities from '@rhythm-game-utilities/core';

const bpm = 120;
const currentTime = 10;
const delta = 0.05;

const isOnTheBeat = RhythmGameUtilities.IsOnTheBeat(bpm, currentTime, delta);

console.log(isOnTheBeat ? 'Is on the beat!' : 'Is not on the beat!'); // Is on the beat!
