#### `Utilities.CalculateTiming`

> Languages: `C#` `C++` `GDScript` `JavaScript`

##### C#

```csharp
// Documentation/API/Utilities/CalculateTiming.cs
using System;
using RhythmGameUtilities;

const int seconds = 2;
const int resolution = 192;
const int positionDelta = 50;

var tempoChanges = new Tempo[] { new() { Position = 0, BPM = 120000 } };

var note = new Note { Position = 750 };

var currentPosition = Utilities.ConvertSecondsToTicks(seconds, resolution, tempoChanges);

var timing = Utilities.CalculateTiming(note.Position, currentPosition, positionDelta);

Console.WriteLine(timing); // Hit
```

##### C++

```cpp
// Documentation/API/Utilities/CalculateTiming.cpp
#include <iostream>

#include "RhythmGameUtilities/Utilities.hpp"

using namespace RhythmGameUtilities;

auto main() -> int
{
    const int seconds = 2;
    const int resolution = 192;
    const int positionDelta = 50;

    std::vector<Tempo> tempoChanges = {{0, 120000}};

    auto note = new Note{1, 750, 0, 0};
    auto currentPosition =
        ConvertSecondsToTicks(seconds, resolution, tempoChanges);

    auto timing =
        CalculateTiming(note->Position, currentPosition, positionDelta);

    std::cout << ToString(timing) << std::endl; // Hit

    return 0;
}
```

##### GDScript

```gdscript
# Documentation/API/Utilities/CalculateTiming.gd
extends Node

func _ready() -> void:
	var seconds: int = 2
	var resolution: int = 192
	var position_delta: int = 50

	var tempo_changes: Array = [
		{"position": 0, "bpm": 120000}
	]

	var current_position: int = rhythm_game_utilities.convert_seconds_to_ticks(seconds, resolution, tempo_changes)

	var timing: int = rhythm_game_utilities.calculate_timing(750, current_position, position_delta)

	match timing:
		rhythm_game_utilities.Miss:
			print("Miss")
		rhythm_game_utilities.Hit:
			print("Hit")
		rhythm_game_utilities.Early:
			print("Early")
		rhythm_game_utilities.Late:
			print("Late")
```

##### JavaScript

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
