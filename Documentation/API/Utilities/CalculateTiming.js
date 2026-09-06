import RhythmGameUtilities from '@rhythm-game-utilities/core';

const seconds = 2;
const resolution = 192;
const positionDelta = 50;

const tempoChanges = [{ position: 0, bpm: 120000 }];

const currentPosition = RhythmGameUtilities.ConvertSecondsToTicks(seconds, resolution, tempoChanges);

const timing = RhythmGameUtilities.CalculateTiming(750, currentPosition, positionDelta);

console.log(timing); // Hit
