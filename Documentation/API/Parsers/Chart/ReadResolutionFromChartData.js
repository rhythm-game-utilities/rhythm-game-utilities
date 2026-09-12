import { readFileSync } from 'node:fs';

import RhythmGameUtilities from '@rhythm-game-utilities/core';

const contents = readFileSync('./tests/Mocks/song.chart', 'utf-8');

const resolution = RhythmGameUtilities.ReadResolutionFromChartData(contents);

console.log(resolution); // 192
