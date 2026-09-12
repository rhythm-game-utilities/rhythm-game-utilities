import { readFileSync } from 'node:fs';

import RhythmGameUtilities from '@rhythm-game-utilities/core';

const contents = readFileSync('./tests/Mocks/song.chart', 'utf-8');

const timeSignatureChanges = RhythmGameUtilities.ReadTimeSignatureChangesFromChartData(contents);

console.log(timeSignatureChanges.length); // 4
