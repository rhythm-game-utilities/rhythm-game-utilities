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

// Common

export function Lerp(a: number, b: number, t: number) {
  return instance.Lerp(a, b, t);
}
export function InverseLerp(a: number, b: number, v: number) {
  return instance.InverseLerp(a, b, v);
}
export function InverseLerpUnclamped(a: number, b: number, v: number) {
  return instance.InverseLerpUnclamped(a, b, v);
}

// Utilities

export function ConvertTickToPosition(tick: number, resolution: number) {
  return instance.ConvertTickToPosition(tick, resolution);
}
export function IsOnTheBeat(bpm: number, currentTime: number, delta: number) {
  return instance.IsOnTheBeat(bpm, currentTime, delta);
}
export function RoundUpToTheNearestMultiplier(
  value: number,
  multiplier: number
) {
  return instance.RoundUpToTheNearestMultiplier(value, multiplier);
}
export function CalculateAccuracyRatio(
  position: number,
  currentPosition: number,
  delta: number
) {
  return instance.CalculateAccuracyRatio(position, currentPosition, delta);
}
export function CalculateAccuracy(
  position: number,
  currentPosition: number,
  delta: number
) {
  return instance.CalculateAccuracy(position, currentPosition, delta);
}
export function CalculateTiming(
  position: number,
  currentPosition: number,
  delta: number
) {
  return instance.CalculateTiming(position, currentPosition, delta);
}
export function ConvertSecondsToTicks(
  seconds: number,
  resolution: number,
  tempoChanges: Tempo[]
) {
  return instance.ConvertSecondsToTicks(seconds, resolution, tempoChanges);
}
export function CalculateBeatBars(
  tempoChanges: Tempo[],
  resolution: number,
  includeHalfNotes: boolean
): BeatBar[] {
  return instance.CalculateBeatBars(tempoChanges, resolution, includeHalfNotes);
}
export function FindNotesNearGivenTick(
  notes: Note[],
  tick: number,
  delta: number
): Note[] {
  return instance.FindNotesNearGivenTick(notes, tick, delta);
}

// Parsers (Chart)

export function ReadResolutionFromChartData(contents: string) {
  return instance.ReadResolutionFromChartData(contents);
}
export function ReadTempoChangesFromChartData(contents: string): Tempo[] {
  return instance.ReadTempoChangesFromChartData(contents);
}
export function ReadTimeSignatureChangesFromChartData(
  contents: string
): TimeSignature[] {
  return instance.ReadTimeSignatureChangesFromChartData(contents);
}
export function ReadNotesFromChartData(
  contents: string,
  difficulty: Difficulty
): Note[] {
  return instance.ReadNotesFromChartData(contents, difficulty);
}

// Parsers (Midi)

export function ReadResolutionFromMidiData(data: Uint8Array) {
  return instance.ReadResolutionFromMidiData(data);
}
export function ReadTempoChangesFromMidiData(data: Uint8Array): Tempo[] {
  return instance.ReadTempoChangesFromMidiData(data);
}
export function ReadTimeSignatureChangesFromMidiData(
  data: Uint8Array
): TimeSignature[] {
  return instance.ReadTimeSignatureChangesFromMidiData(data);
}
export function ReadNotesFromMidiData(data: Uint8Array): Note[] {
  return instance.ReadNotesFromMidiData(data);
}

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
  ReadNotesFromChartData,

  ReadResolutionFromMidiData,
  ReadTempoChangesFromMidiData,
  ReadTimeSignatureChangesFromMidiData,
  ReadNotesFromMidiData
};
