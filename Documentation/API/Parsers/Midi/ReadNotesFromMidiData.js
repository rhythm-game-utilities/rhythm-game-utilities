import { readFileSync } from 'node:fs';

import RhythmGameUtilities from '@rhythm-game-utilities/core';

const data = readFileSync('./tests/Mocks/song.mid');

const notes = RhythmGameUtilities.ReadNotesFromMidiData(data);

for (let note of notes) {
  console.log(`${note.position} ${note.handPosition}`);
}
