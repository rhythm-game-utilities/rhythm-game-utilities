import { RhythmGameUtilities } from './instance.js';

export default {
  Lerp(a, b, t) {
    if (!RhythmGameUtilities) {
      return -1;
    }
    return RhythmGameUtilities.Lerp(a, b, t);
  },
  InverseLerp(a, b, v) {
    if (!RhythmGameUtilities) {
      return -1;
    }
    return RhythmGameUtilities.InverseLerp(a, b, v);
  },
  InverseLerpUnclamped(a, b, v) {
    if (!RhythmGameUtilities) {
      return -1;
    }
    return RhythmGameUtilities.InverseLerpUnclamped(a, b, v);
  },
  ConvertTickToPosition(tick, resolution) {
    if (!RhythmGameUtilities) {
      return -1;
    }
    return RhythmGameUtilities.ConvertTickToPosition(tick, resolution);
  },
  IsOnTheBeat(bpm, currentTime, delta) {
    if (!RhythmGameUtilities) {
      return -1;
    }
    return RhythmGameUtilities.IsOnTheBeat(bpm, currentTime, delta);
  },
  RoundUpToTheNearestMultiplier(value, multiplier) {
    if (!RhythmGameUtilities) {
      return -1;
    }
    return RhythmGameUtilities.RoundUpToTheNearestMultiplier(value, multiplier);
  },
  CalculateAccuracyRatio(position, currentPosition, delta) {
    if (!RhythmGameUtilities) {
      return -1;
    }
    return RhythmGameUtilities.CalculateAccuracyRatio(position, currentPosition, delta);
  },
  CalculateAccuracy(position, currentPosition, delta) {
    if (!RhythmGameUtilities) {
      return '';
    }
    return RhythmGameUtilities.CalculateAccuracy(position, currentPosition, delta);
  },
  CalculateTiming(position, currentPosition, delta) {
    if (!RhythmGameUtilities) {
      return '';
    }
    return RhythmGameUtilities.CalculateTiming(position, currentPosition, delta);
  },
  ConvertSecondsToTicks(seconds, resolution, tempoChanges) {
    if (!RhythmGameUtilities) {
      return -1;
    }
    return RhythmGameUtilities.ConvertSecondsToTicks(seconds, resolution, tempoChanges);
  },
  CalculateBeatBars(tempoChanges, resolution, includeHalfNotes) {
    if (!RhythmGameUtilities) {
      return '';
    }
    return RhythmGameUtilities.CalculateBeatBars(tempoChanges, resolution, includeHalfNotes);
  },
  FindNotesNearGivenTick(notes, tick, delta) {
    if (!RhythmGameUtilities) {
      return '';
    }
    return RhythmGameUtilities.FindNotesNearGivenTick(notes, tick, delta);
  },
  ReadResolutionFromChartData(contents) {
    if (!RhythmGameUtilities) {
      return -1;
    }
    return RhythmGameUtilities.ReadResolutionFromChartData(contents);
  },
  ReadTempoChangesFromChartData(contents) {
    if (!RhythmGameUtilities) {
      return '';
    }
    return RhythmGameUtilities.ReadTempoChangesFromChartData(contents);
  },
  ReadTimeSignatureChangesFromChartData(contents) {
    if (!RhythmGameUtilities) {
      return '';
    }
    return RhythmGameUtilities.ReadTimeSignatureChangesFromChartData(contents);
  },
  ReadNotesFromChartData(contents, difficulty) {
    if (!RhythmGameUtilities) {
      return '';
    }
    return RhythmGameUtilities.ReadNotesFromChartData(contents, difficulty);
  },
  ReadResolutionFromMidiData(data) {
    if (!RhythmGameUtilities) {
      return -1;
    }
    return RhythmGameUtilities.ReadResolutionFromMidiData(data);
  },
  ReadTempoChangesFromMidiData(data) {
    if (!RhythmGameUtilities) {
      return '';
    }
    return RhythmGameUtilities.ReadTempoChangesFromMidiData(data);
  },
  ReadTimeSignatureChangesFromMidiData(data) {
    if (!RhythmGameUtilities) {
      return '';
    }
    return RhythmGameUtilities.ReadTimeSignatureChangesFromMidiData(data);
  },
  ReadNotesFromMidiData(data) {
    if (!RhythmGameUtilities) {
      return '';
    }
    return RhythmGameUtilities.ReadNotesFromMidiData(data);
  }
};
