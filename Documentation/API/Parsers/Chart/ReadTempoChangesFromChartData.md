#### `Chart.ReadTempoChangesFromChartData`

> Languages: `C#` `C++` `GDScript`

##### C#

```csharp
// Documentation/API/Parsers/Chart/ReadTempoChangesFromChartData.cs
using System;
using System.IO;
using RhythmGameUtilities;

var contents = File.ReadAllText("./song.chart");

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
    auto contents = ReadStringFromFile("./song.chart");

    auto tempoChanges = ReadTempoChangesFromChartData(contents.c_str());

    std::cout << size(tempoChanges) << std::endl; // 7

    return 0;
}
```

##### GDScript

```gdscript
extends Node

func _ready() -> void:
	var file: FileAccess = FileAccess.open("res://song.chart", FileAccess.READ)
	var contents: String = file.get_as_text()

	var tempo_changes: Array = rhythm_game_utilities.read_tempo_changes_from_chart_data(contents)

	print(tempo_changes)
```

##### Lua

```lua
-- Documentation/API/Parsers/Chart/ReadTempoChangesFromChartData.lua
---@type RhythmGameUtilities
local rhythmgameutilities = require("rhythmgameutilities")

local function get_table_length(table)
    local count = 0
    for _ in pairs(table) do
        count = count + 1
    end
    return count
end

local file = io.open("../tests/Mocks/song.chart", "r")

if file then
    local content = file:read("*a")

    local value = rhythmgameutilities.read_tempo_changes_from_chart_data(content);

    print(get_table_length(value))
end
```
