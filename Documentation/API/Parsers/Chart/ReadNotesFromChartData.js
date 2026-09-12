import { readFileSync } from 'node:fs';

import RhythmGameUtilities from '@rhythm-game-utilities/core';

const contents = readFileSync('./tests/Mocks/song.chart', 'utf-8');

const notes = RhythmGameUtilities.ReadNotesFromChartData(contents, 'Expert');

for (let note of notes) {
  console.log(`${note.position} ${note.handPosition}`);
}
