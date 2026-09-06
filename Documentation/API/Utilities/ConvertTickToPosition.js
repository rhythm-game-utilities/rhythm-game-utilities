import RhythmGameUtilities from '@rhythm-game-utilities/core';

const tick = 1056;
const resolution = 192;

const position = RhythmGameUtilities.ConvertTickToPosition(tick, resolution);

console.log(position); // 5.5
