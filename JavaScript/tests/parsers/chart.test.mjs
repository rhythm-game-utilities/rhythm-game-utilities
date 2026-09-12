/* node:coverage disable */

import test, { describe } from 'node:test';
import assert from 'node:assert';

import { readFileSync } from 'node:fs';

import RhythmGameUtilities from '@rhythm-game-utilities/core';

describe('Parsers', () => {
  describe('Chart', () => {
    test('ReadResolutionFromChartData', () => {
      assert.equal(RhythmGameUtilities.ReadResolutionFromChartData(readFileSync('./tests/Mocks/song.chart', 'utf-8')), 192);
    });

    test('ReadTempoChangesFromChartData', () => {
      const tempoChanges = RhythmGameUtilities.ReadTempoChangesFromChartData(readFileSync('./tests/Mocks/song.chart', 'utf-8'));

      assert.equal(tempoChanges.length, 7);
    });

    test('ReadTimeSignatureChangesFromChartData', () => {
      const timeSignatureChanges = RhythmGameUtilities.ReadTimeSignatureChangesFromChartData(readFileSync('./tests/Mocks/song.chart', 'utf-8'));

      assert.equal(timeSignatureChanges.length, 4);
    });

    test('ReadNotesFromChartData', () => {
      const notes = RhythmGameUtilities.ReadNotesFromChartData(readFileSync('./tests/Mocks/song.chart', 'utf-8'), 'Expert');

      assert.equal(notes.length, 8);
    });
  });
});
