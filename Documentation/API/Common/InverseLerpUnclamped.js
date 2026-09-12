import RhythmGameUtilities from '@rhythm-game-utilities/core';

const value = RhythmGameUtilities.InverseLerpUnclamped(0, 10, 11);

console.log(value.toFixed(1)); // 1.1
