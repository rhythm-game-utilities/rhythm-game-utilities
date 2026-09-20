// prettier-ignore

import RhythmGameUtilitiesModule from "@rhythm-game-utilities/core/module";

export type Difficulty = 'Easy' | 'Medium' | 'Hard' | 'Expert';

export type BeatBar = {
  position: number;
  bpm: number;
};

export type Tempo = {
  position: number;
  bpm: number;
};

export type Note = {
  id: number;
  position: number;
  handPosition: number;
  length: number;
};

export type TimeSignature = {
  position: number;
  numerator: number;
  denominator: number;
};

const instance = await RhythmGameUtilitiesModule();

// Commong

export const Lerp = (a: number, b: number, t: number) => instance.Lerp(a, b, t);
export const InverseLerp = (a: number, b: number, v: number) => instance.InverseLerp(a, b, v);
export const InverseLerpUnclamped = (a: number, b: number, v: number) => instance.InverseLerpUnclamped(a, b, v);

// Utilities

export const ConvertTickToPosition = (tick: number, resolution: number) => instance.ConvertTickToPosition(tick, resolution);
export const IsOnTheBeat = (bpm: number, currentTime: number, delta: number) => instance.IsOnTheBeat(bpm, currentTime, delta);
export const RoundUpToTheNearestMultiplier = (value: number, multiplier: number) => instance.RoundUpToTheNearestMultiplier(value, multiplier);
export const CalculateAccuracyRatio = (position: number, currentPosition: number, delta: number) => instance.CalculateAccuracyRatio(position, currentPosition, delta);
export const CalculateAccuracy = (position: number, currentPosition: number, delta: number) => instance.CalculateAccuracy(position, currentPosition, delta);
export const CalculateTiming = (position: number, currentPosition: number, delta: number) => instance.CalculateTiming(position, currentPosition, delta);
export const ConvertSecondsToTicks = (seconds: number, resolution: number, tempoChanges: Tempo[]) => instance.ConvertSecondsToTicks(seconds, resolution, tempoChanges);
export const CalculateBeatBars = (tempoChanges: Tempo[], resolution: number, includeHalfNotes: boolean): BeatBar[] => instance.CalculateBeatBars(tempoChanges, resolution, includeHalfNotes);
export const FindNotesNearGivenTick = (notes: Note[], tick: number, delta: number): Note[] => instance.FindNotesNearGivenTick(notes, tick, delta);

// Parsers (Chart)

export const ReadResolutionFromChartData = (contents: string) => instance.ReadResolutionFromChartData(contents);
export const ReadTempoChangesFromChartData = (contents: string): Tempo[] => instance.ReadTempoChangesFromChartData(contents);
export const ReadTimeSignatureChangesFromChartData = (contents: string): TimeSignature[] => instance.ReadTimeSignatureChangesFromChartData(contents);
export const ReadNotesFromChartData = (contents: string, difficulty: Difficulty): Note[] => instance.ReadNotesFromChartData(contents, difficulty);

export default {
  Lerp,
  InverseLerp,
  InverseLerpUnclamped,

  ConvertTickToPosition,
  IsOnTheBeat,
  RoundUpToTheNearestMultiplier,
  CalculateAccuracyRatio,
  CalculateAccuracy,
  CalculateTiming,
  ConvertSecondsToTicks,
  CalculateBeatBars,
  FindNotesNearGivenTick,

  ReadResolutionFromChartData,
  ReadTempoChangesFromChartData,
  ReadTimeSignatureChangesFromChartData,
  ReadNotesFromChartData
};
