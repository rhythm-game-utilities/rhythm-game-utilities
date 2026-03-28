#### `Utilities.CalculateBeatBars`

> Languages: `C#` `C++` `GDScript`

##### C#

```csharp
using System;
using RhythmGameUtilities;

const int resolution = 192;

var tempoChanges = new Tempo[]
{
    new() { Position = 0, BPM = 88000 }, new() { Position = 3840, BPM = 112000 },
    new() { Position = 9984, BPM = 89600 }, new() { Position = 22272, BPM = 112000 },
    new() { Position = 33792, BPM = 111500 }, new() { Position = 34560, BPM = 112000 },
    new() { Position = 42240, BPM = 111980 }
};

var beatBars = Utilities.CalculateBeatBars(tempoChanges, resolution, true);

Console.WriteLine(beatBars.Length); // 440
```

##### C++

```cpp
// Documentation/API/Utilities/CalculateBeatBars.cpp
#include <iostream>

#include "RhythmGameUtilities/Utilities.hpp"

using namespace RhythmGameUtilities;

auto main() -> int
{
    const int resolution = 192;

    std::vector<Tempo> tempoChanges = {
        {0, 88000},      {3840, 112000},  {9984, 89600},  {22272, 112000},
        {33792, 111500}, {34560, 112000}, {42240, 111980}};

    auto beatBars = CalculateBeatBars(tempoChanges, resolution, true);

    std::cout << size(beatBars) << std::endl; // 440

    return 0;
}
```

##### GDScript

```gdscript
extends Node

func _ready() -> void:
	var resolution: int = 192

	var tempo_changes: Array = [
		{"position": 0, "bpm": 8800},
		{"position": 3840, "bpm": 112000},
		{"position": 9984, "bpm": 89600},
		{"position": 22272, "bpm": 112000},
		{"position": 33792, "bpm": 111500},
		{"position": 34560, "bpm": 112000},
		{"position": 42240, "bpm": 111980}
	]

	var beat_bars: Array = rhythm_game_utilities.calculate_beat_bars(tempo_changes, resolution, true)

	print(beat_bars)
```
