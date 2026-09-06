#### `Chart.ReadResolutionFromChartData`

> Languages: `C#` `C++` `GDScript`

##### C#

```csharp
// Documentation/API/Parsers/Chart/ReadResolutionFromChartData.cs
using System;
using System.IO;
using RhythmGameUtilities;

var contents = File.ReadAllText("./Tests/mocks/song.chart");

var resolution = Chart.ReadResolutionFromChartData(contents);

Console.WriteLine(resolution); // 192
```

##### C++

```cpp
// Documentation/API/Parsers/Chart/ReadResolutionFromChartData.cpp
#include <iostream>

#include "RhythmGameUtilities/File.hpp"
#include "RhythmGameUtilities/Parsers/Chart.hpp"

using namespace RhythmGameUtilities;

auto main() -> int
{
    auto contents = ReadStringFromFile("./Tests/mocks/song.chart");

    auto resolution = ReadResolutionFromChartData(contents.c_str());

    std::cout << resolution << std::endl;

    return 0;
}
```

##### GDScript

```gdscript
# Documentation/API/Parsers/Chart/ReadResolutionFromChartData.gd
extends Node

func _ready() -> void:
	var file: FileAccess = FileAccess.open("res://song.chart", FileAccess.READ)
	var contents: String = file.get_as_text()

	var resolution: int = rhythm_game_utilities.read_resolution_from_chart_data(contents)

	print(resolution)
```

##### JavaScript

```javascript
// Documentation/API/Parsers/Chart/ReadResolutionFromChartData.js
import { readFileSync } from 'node:fs';

import RhythmGameUtilities from '@rhythm-game-utilities/core';

const contents = readFileSync('./tests/mocks/song.chart', 'utf-8');

const resolution = RhythmGameUtilities.ReadResolutionFromChartData(contents);

console.log(resolution); // 192
```
