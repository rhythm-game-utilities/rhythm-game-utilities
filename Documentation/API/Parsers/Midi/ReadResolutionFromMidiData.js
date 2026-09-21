import { readFileSync } from 'node:fs';

import RhythmGameUtilities from '@rhythm-game-utilities/core';

const data = readFileSync('./tests/Mocks/song.mid');

const resolution = RhythmGameUtilities.ReadResolutionFromMidiData(data);

console.log(resolution); // 480
