import { readFileSync } from 'node:fs';

import RhythmGameUtilities from '@rhythm-game-utilities/core';

const contents = readFileSync('./tests/mocks/song.chart', 'utf-8');

const tempoChanges = RhythmGameUtilities.ReadTempoChangesFromChartData(contents);

console.log(tempoChanges.length); // 7
