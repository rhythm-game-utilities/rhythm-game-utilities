# rhythm-game-utilities

> A collection of utilities for creating rhythm games in Unity, Unreal, Godot, SDL and MonoGame.

## Install

```bash
$ npm install @rhythm-game-utilities/core
```

## Usage

### ReadNotesFromChartData

```javascript
// Documentation/API/Parsers/Chart/ReadNotesFromChartData.js
import { readFileSync } from 'node:fs';

import RhythmGameUtilities from '@rhythm-game-utilities/core';

const contents = readFileSync('./tests/Mocks/song.chart', 'utf-8');

const notes = RhythmGameUtilities.ReadNotesFromChartData(contents, 'Expert');

console.log(notes.length); // 8
```

### ReadTimeSignatureChangesFromChartData

```javascript
// Documentation/API/Parsers/Chart/ReadTimeSignatureChangesFromChartData.js
import { readFileSync } from 'node:fs';

import RhythmGameUtilities from '@rhythm-game-utilities/core';

const contents = readFileSync('./tests/Mocks/song.chart', 'utf-8');

const timeSignatureChanges = RhythmGameUtilities.ReadTimeSignatureChangesFromChartData(contents);

console.log(timeSignatureChanges.length); // 4
```

### ReadResolutionFromChartData

```javascript
// Documentation/API/Parsers/Chart/ReadResolutionFromChartData.js
import { readFileSync } from 'node:fs';

import RhythmGameUtilities from '@rhythm-game-utilities/core';

const contents = readFileSync('./tests/Mocks/song.chart', 'utf-8');

const resolution = RhythmGameUtilities.ReadResolutionFromChartData(contents);

console.log(resolution); // 192
```

### ReadTempoChangesFromChartData

```javascript
// Documentation/API/Parsers/Chart/ReadTempoChangesFromChartData.js
import { readFileSync } from 'node:fs';

import RhythmGameUtilities from '@rhythm-game-utilities/core';

const contents = readFileSync('./tests/Mocks/song.chart', 'utf-8');

const tempoChanges = RhythmGameUtilities.ReadTempoChangesFromChartData(contents);

console.log(tempoChanges.length); // 7
```

### IsOnTheBeat

```javascript
// Documentation/API/Utilities/IsOnTheBeat.js
import RhythmGameUtilities from '@rhythm-game-utilities/core';

const bpm = 120;
const currentTime = 10;
const delta = 0.05;

const isOnTheBeat = RhythmGameUtilities.IsOnTheBeat(bpm, currentTime, delta);

console.log(isOnTheBeat); // true
```

### ConvertSecondsToTicks

```javascript
// Documentation/API/Utilities/ConvertSecondsToTicks.js
import RhythmGameUtilities from '@rhythm-game-utilities/core';

const seconds = 5;
const resolution = 192;

var tempoChanges = [
  { position: 0, bpm: 88000 },
  { position: 3840, bpm: 112000 },
  { position: 9984, bpm: 89600 },
  { position: 22272, bpm: 112000 },
  { position: 33792, bpm: 111500 },
  { position: 34560, bpm: 112000 },
  { position: 42240, bpm: 111980 }
];

var ticks = RhythmGameUtilities.ConvertSecondsToTicks(seconds, resolution, tempoChanges);

console.log(ticks); // 1408
```

### FindNotesNearGivenTick

```javascript
// Documentation/API/Utilities/FindNotesNearGivenTick.js
import RhythmGameUtilities from '@rhythm-game-utilities/core';

const delta = 50;

const notes = [
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
];

const foundNotes = RhythmGameUtilities.FindNotesNearGivenTick(notes, 160, delta);

console.log(foundNotes.length); // 5
```

### CalculateBeatBars

```javascript
// Documentation/API/Utilities/CalculateBeatBars.js
import RhythmGameUtilities from '@rhythm-game-utilities/core';

const tempoChanges = [
  { position: 0, bpm: 88000 },
  { position: 3840, bpm: 112000 },
  { position: 9984, bpm: 89600 },
  { position: 22272, bpm: 112000 },
  { position: 33792, bpm: 111500 },
  { position: 34560, bpm: 112000 },
  { position: 42240, bpm: 111980 }
];

const resolution = 192;

const beatBars = RhythmGameUtilities.CalculateBeatBars(tempoChanges, resolution, true);

console.log(beatBars.length); // 440
```

### CalculateAccuracyRatio

```javascript
// Documentation/API/Utilities/CalculateAccuracyRatio.js
import RhythmGameUtilities from '@rhythm-game-utilities/core';

const seconds = 2;
const resolution = 192;
const positionDelta = 50;

const tempoChanges = [{ position: 0, bpm: 120000 }];

const currentPosition = RhythmGameUtilities.ConvertSecondsToTicks(seconds, resolution, tempoChanges);

const accuracyRatio = RhythmGameUtilities.CalculateAccuracyRatio(750, currentPosition, positionDelta);

console.log(accuracyRatio); // -0.36
```

### CalculateAccuracy

```javascript
// Documentation/API/Utilities/CalculateAccuracy.js
import RhythmGameUtilities from '@rhythm-game-utilities/core';

const seconds = 2;
const resolution = 192;
const positionDelta = 50;

const tempoChanges = [{ position: 0, bpm: 120000 }];

const currentPosition = RhythmGameUtilities.ConvertSecondsToTicks(seconds, resolution, tempoChanges);

const accuracy = RhythmGameUtilities.CalculateAccuracy(750, currentPosition, positionDelta);

console.log(accuracy); // Good
```

### RoundUpToTheNearestMultiplier

```javascript
// Documentation/API/Utilities/RoundUpToTheNearestMultiplier.js
import RhythmGameUtilities from '@rhythm-game-utilities/core';

const value = RhythmGameUtilities.RoundUpToTheNearestMultiplier(12, 10);

console.log(value); // 20
```

### CalculateTiming

```javascript
// Documentation/API/Utilities/CalculateTiming.js
import RhythmGameUtilities from '@rhythm-game-utilities/core';

const seconds = 2;
const resolution = 192;
const positionDelta = 50;

const tempoChanges = [{ position: 0, bpm: 120000 }];

const currentPosition = RhythmGameUtilities.ConvertSecondsToTicks(seconds, resolution, tempoChanges);

const timing = RhythmGameUtilities.CalculateTiming(750, currentPosition, positionDelta);

console.log(timing); // Hit
```

### ConvertTickToPosition

```javascript
// Documentation/API/Utilities/ConvertTickToPosition.js
import RhythmGameUtilities from '@rhythm-game-utilities/core';

const tick = 1056;
const resolution = 192;

const position = RhythmGameUtilities.ConvertTickToPosition(tick, resolution);

console.log(position); // 5.5
```

### InverseLerpUnclamped

```javascript
// Documentation/API/Common/InverseLerpUnclamped.js
import RhythmGameUtilities from '@rhythm-game-utilities/core';

const value = RhythmGameUtilities.InverseLerpUnclamped(0, 10, 11);

console.log(value); // 1.1
```

### Lerp

```javascript
// Documentation/API/Common/Lerp.js
import RhythmGameUtilities from '@rhythm-game-utilities/core';

const value = RhythmGameUtilities.Lerp(0, 10, 0.5);

console.log(value); // 5
```

### InverseLerp

```javascript
// Documentation/API/Common/InverseLerp.js
import RhythmGameUtilities from '@rhythm-game-utilities/core';

const value = RhythmGameUtilities.InverseLerp(0, 10, 5);

console.log(value); // 0.5
```
