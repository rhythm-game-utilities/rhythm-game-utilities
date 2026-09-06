import { readFileSync } from 'node:fs';

import RhythmGameUtilities from '@rhythm-game-utilities/core';

const contents = readFileSync('./tests/mocks/song.chart', 'utf-8');

const notes = RhythmGameUtilities.ReadNotesFromChartData(contents, 'Expert');

console.log(notes.length); // 8
