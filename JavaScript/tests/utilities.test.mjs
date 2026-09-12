/* node:coverage disable */

import test, { describe } from 'node:test';
import assert from 'node:assert';

import RhythmGameUtilities from '@rhythm-game-utilities/core';

describe('Utilities', () => {
  test('ConvertSecondsToTicks', () => {
    assert.equal(
      RhythmGameUtilities.ConvertSecondsToTicks(5, 192, [
        { position: 0, bpm: 88000 },
        { position: 3840, bpm: 112000 },
        { position: 9984, bpm: 89600 },
        { position: 22272, bpm: 112000 },
        { position: 33792, bpm: 111500 },
        { position: 34560, bpm: 112000 },
        { position: 42240, bpm: 111980 }
      ]),
      1408
    );
  });
  test('CalculateBeatBars', () => {
    assert.equal(
      RhythmGameUtilities.CalculateBeatBars(
        [
          { position: 0, bpm: 88000 },
          { position: 3840, bpm: 112000 },
          { position: 9984, bpm: 89600 },
          { position: 22272, bpm: 112000 },
          { position: 33792, bpm: 111500 },
          { position: 34560, bpm: 112000 },
          { position: 42240, bpm: 111980 }
        ],
        192,
        true
      ).length,
      440
    );
  });
  test('FindNotesNearGivenTick', () => {
    assert.equal(
      RhythmGameUtilities.FindNotesNearGivenTick(
        [
          { id: 1, position: 110 },
          { id: 2, position: 120 },
          { id: 3, position: 130 },
          { id: 4, position: 140 },
          { id: 5, position: 150 },
          { id: 6, position: 160 },
          { id: 7, position: 170 },
          { id: 8, position: 180 },
          { id: 9, position: 190 },
          { id: 10, position: 200 }
        ],
        160,
        20
      ).length,
      5
    );
  });
  test('ConvertTickToPosition', () => {
    assert.ok(Math.abs(5.5 - RhythmGameUtilities.ConvertTickToPosition(1056, 192)) < 0.01);
  });
  test('IsOnTheBeat', () => {
    assert.ok(RhythmGameUtilities.IsOnTheBeat(120, 10, 0.5));
    assert.ok(RhythmGameUtilities.IsOnTheBeat(60, 1, 0.5));
    assert.ok(!RhythmGameUtilities.IsOnTheBeat(60, 1.5, 0.5));
  });
  test('RoundUpToTheNearestMultiplier', () => {
    assert.equal(RhythmGameUtilities.RoundUpToTheNearestMultiplier(12, 10), 20);
  });
  test('CalculateAccuracyRatio', () => {
    const seconds = 2;
    const resolution = 192;
    const positionDelta = 50;

    const tempoChanges = [{ position: 0, bpm: 120000 }];

    const currentPosition = RhythmGameUtilities.ConvertSecondsToTicks(seconds, resolution, tempoChanges);

    const value = RhythmGameUtilities.CalculateAccuracyRatio(750, currentPosition, positionDelta);

    assert.ok(Math.abs(0.36 - Math.abs(value)) < 0.01);
  });
  test('CalculateAccuracy', () => {
    const seconds = 2;
    const resolution = 192;
    const positionDelta = 50;

    const tempoChanges = [{ position: 0, bpm: 120000 }];

    const currentPosition = RhythmGameUtilities.ConvertSecondsToTicks(seconds, resolution, tempoChanges);

    assert.equal(RhythmGameUtilities.CalculateAccuracy(750, currentPosition, positionDelta), 'Good');
  });
  test('CalculateTiming', () => {
    const seconds = 2;
    const resolution = 192;
    const positionDelta = 50;

    const tempoChanges = [{ position: 0, bpm: 120000 }];

    const currentPosition = RhythmGameUtilities.ConvertSecondsToTicks(seconds, resolution, tempoChanges);

    assert.equal(RhythmGameUtilities.CalculateTiming(750, currentPosition, positionDelta), 'Hit');
  });
});
