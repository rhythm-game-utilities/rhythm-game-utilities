import { readFileSync } from 'node:fs';

import RhythmGameUtilities from '@rhythm-game-utilities/core';

const data = readFileSync('./tests/Mocks/song.mid');

const timeSignatureChanges =
  RhythmGameUtilities.ReadTimeSignatureChangesFromMidiData(data);

console.log(timeSignatureChanges.length); // 1
