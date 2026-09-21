/* node:coverage disable */

import test, { describe } from 'node:test';
import assert from 'node:assert';

import { readFileSync } from 'node:fs';

import RhythmGameUtilities from '@rhythm-game-utilities/core';

describe('Parsers', () => {
  describe('Midi', () => {
    test('ReadResolutionFromMidiData', () => {
      assert.equal(RhythmGameUtilities.ReadResolutionFromMidiData(readFileSync('./tests/mocks/song.mid')), 480);
    });

    test('ReadTempoChangesFromMidiData', () => {
      const tempoChanges = RhythmGameUtilities.ReadTempoChangesFromMidiData(readFileSync('./tests/mocks/song.mid'));

      assert.equal(tempoChanges.length, 1);
    });

    test('ReadTimeSignatureChangesFromMidiData', () => {
      const timeSignatureChanges = RhythmGameUtilities.ReadTimeSignatureChangesFromMidiData(readFileSync('./tests/mocks/song.mid'));

      assert.equal(timeSignatureChanges.length, 1);
    });
    test('ReadNotesFromMidiData', () => {
      const notes = RhythmGameUtilities.ReadNotesFromMidiData(readFileSync('./tests/mocks/song.mid'));

      assert.equal(notes.length, 10);
    });
  });
});
