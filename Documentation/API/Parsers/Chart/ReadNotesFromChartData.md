#### `Chart.ReadNotesFromChartData`

> Languages: `C#` `C++` `GDScript` `JavaScript`

##### C#

```csharp
// Documentation/API/Parsers/Chart/ReadNotesFromChartData.cs
using System;
using System.IO;
using RhythmGameUtilities;

var contents = File.ReadAllText("./tests/Mocks/song.chart");

var notes = Chart.ReadNotesFromChartData(contents, Difficulty.Expert);

Console.WriteLine(notes.Length); // 8
```

##### C++

```cpp
// Documentation/API/Parsers/Chart/ReadNotesFromChartData.cpp
#include <iostream>

#include "RhythmGameUtilities/File.hpp"
#include "RhythmGameUtilities/Parsers/Chart.hpp"

using namespace RhythmGameUtilities;

auto main() -> int
{
    auto contents = ReadStringFromFile("./tests/Mocks/song.chart");

    auto notes = ReadNotesFromChartData(contents.c_str(), Difficulty::Expert);

    for (const auto &note : notes)
    {
        if (note.HandPosition > 5)
        {
            continue;
        }

        std::cout << note.Position << " " << note.HandPosition << std::endl;
    }

    return 0;
}
```

##### GDScript

```gdscript
# Documentation/API/Parsers/Chart/ReadNotesFromChartData.gd
extends Node

func _ready() -> void:
	var file: FileAccess = FileAccess.open("res://song.chart", FileAccess.READ)
	var contents: String = file.get_as_text()

	var notes: Array = rhythm_game_utilities.read_notes_from_chart_data(contents, rhythm_game_utilities.Expert)

	print(notes)
```

##### JavaScript

```javascript
// Documentation/API/Parsers/Chart/ReadNotesFromChartData.js
import { readFileSync } from 'node:fs';

import RhythmGameUtilities from '@rhythm-game-utilities/core';

const contents = readFileSync('./tests/Mocks/song.chart', 'utf-8');

const notes = RhythmGameUtilities.ReadNotesFromChartData(contents, 'Expert');

console.log(notes.length); // 8
```
