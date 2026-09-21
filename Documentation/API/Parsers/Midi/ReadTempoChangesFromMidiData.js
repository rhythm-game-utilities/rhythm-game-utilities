import { readFileSync } from 'node:fs';

import RhythmGameUtilities from '@rhythm-game-utilities/core';

const data = readFileSync('./tests/Mocks/song.mid');

const tempoChanges = RhythmGameUtilities.ReadTempoChangesFromMidiData(data);

console.log(tempoChanges.length); // 1
