/* node:coverage disable */

import test, { describe } from 'node:test';
import assert from 'node:assert';

import RhythmGameUtilities from '@rhythm-game-utilities/core';

describe('Common', () => {
  test('Lerp', () => {
    assert.equal(RhythmGameUtilities.Lerp(0, 10, 0.5), 5);
  });
  test('LerpUnclamped', () => {
    assert.equal(RhythmGameUtilities.LerpUnclamped(0, 10, 1.1), 11);
  });
  test('InverseLerp', () => {
    assert.ok(Math.abs(0.5 - RhythmGameUtilities.InverseLerp(0, 10, 5)) < 0.01);
  });
  test('InverseLerpUnclamped', () => {
    assert.ok(
      Math.abs(1.1 - RhythmGameUtilities.InverseLerpUnclamped(0, 10, 11)) < 0.01
    );
  });
});
