#### `Chart.ReadTempoChangesFromChartData`

> Languages: `C#` `C++` `GDScript`

##### C#

```csharp
// Documentation/API/Parsers/Chart/ReadTempoChangesFromChartData.cs
using System;
using System.IO;
using RhythmGameUtilities;

var contents = File.ReadAllText("./tests/Mocks/song.chart");

var tempoChanges = Chart.ReadTempoChangesFromChartData(contents);

Console.WriteLine(tempoChanges.Length); // 7
```

##### C++

```cpp
// Documentation/API/Parsers/Chart/ReadTempoChangesFromChartData.cpp
#include <iostream>

#include "RhythmGameUtilities/File.hpp"
#include "RhythmGameUtilities/Parsers/Chart.hpp"

using namespace RhythmGameUtilities;

auto main() -> int
{
    auto contents = ReadStringFromFile("./tests/Mocks/song.chart");

    auto tempoChanges = ReadTempoChangesFromChartData(contents.c_str());

    std::cout << size(tempoChanges) << std::endl; // 7

    return 0;
}
```

##### GDScript

```gdscript
# Documentation/API/Parsers/Chart/ReadTempoChangesFromChartData.gd
extends Node

func _ready() -> void:
	var file: FileAccess = FileAccess.open("res://song.chart", FileAccess.READ)
	var contents: String = file.get_as_text()

	var tempo_changes: Array = rhythm_game_utilities.read_tempo_changes_from_chart_data(contents)

	print(tempo_changes)
```

##### JavaScript

```javascript
// Documentation/API/Parsers/Chart/ReadTempoChangesFromChartData.js
import { readFileSync } from 'node:fs';

import RhythmGameUtilities from '@rhythm-game-utilities/core';

const contents = readFileSync('./tests/Mocks/song.chart', 'utf-8');

const tempoChanges = RhythmGameUtilities.ReadTempoChangesFromChartData(contents);

console.log(tempoChanges.length); // 7
```
