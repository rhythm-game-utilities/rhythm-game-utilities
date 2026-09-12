import RhythmGameUtilities from '@rhythm-game-utilities/core';

const seconds = 2;
const resolution = 192;
const positionDelta = 50;

const tempoChanges = [{ position: 0, bpm: 120000 }];

const currentPosition = RhythmGameUtilities.ConvertSecondsToTicks(seconds, resolution, tempoChanges);

const accuracyRatio = RhythmGameUtilities.CalculateAccuracyRatio(750, currentPosition, positionDelta);

console.log(accuracyRatio); // -0.36
