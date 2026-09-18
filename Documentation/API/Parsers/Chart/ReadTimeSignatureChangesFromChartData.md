#### `Chart.ReadTimeSignatureChangesFromChartData`

> Languages: `C#` `C++` `GDScript` `JavaScript` `Lua`

##### C#

```csharp
// Documentation/API/Parsers/Chart/ReadTimeSignatureChangesFromChartData.cs
using System;
using System.IO;
using RhythmGameUtilities;

var contents = File.ReadAllText("./tests/Mocks/song.chart");

var timeSignatureChanges = Chart.ReadTimeSignatureChangesFromChartData(contents);

Console.WriteLine(timeSignatureChanges.Length); // 4
```

##### C++

```cpp
// Documentation/API/Parsers/Chart/ReadTimeSignatureChangesFromChartData.cpp
#include <iostream>

#include "RhythmGameUtilities/File.hpp"
#include "RhythmGameUtilities/Parsers/Chart.hpp"

using namespace RhythmGameUtilities;

auto main() -> int
{
    auto contents = ReadStringFromFile("./tests/Mocks/song.chart");

    auto timeSignatureChanges =
        ReadTimeSignatureChangesFromChartData(contents.c_str());

    std::cout << size(timeSignatureChanges) << std::endl; // 4

    return 0;
}
```

##### GDScript

```gdscript
# Documentation/API/Parsers/Chart/ReadTimeSignatureChangesFromChartData.gd
extends Node

func _ready() -> void:
	var file: FileAccess = FileAccess.open("res://song.chart", FileAccess.READ)
	var contents: String = file.get_as_text()

	var time_signature_changes: Array = rhythm_game_utilities.read_time_signature_changes_from_chart_data(contents)

	print(time_signature_changes)
```

##### JavaScript

```javascript
// Documentation/API/Parsers/Chart/ReadTimeSignatureChangesFromChartData.js
import { readFileSync } from 'node:fs';

import RhythmGameUtilities from '@rhythm-game-utilities/core';

const contents = readFileSync('./tests/Mocks/song.chart', 'utf-8');

const timeSignatureChanges = RhythmGameUtilities.ReadTimeSignatureChangesFromChartData(contents);

console.log(timeSignatureChanges.length); // 4
```

##### Lua

```lua
-- Documentation/API/Parsers/Chart/ReadTimeSignatureChangesFromChartData.lua
---@type RhythmGameUtilities
local rhythmgameutilities = require("rhythmgameutilities")

local function get_table_length(table)
    local count = 0
    for _ in pairs(table) do
        count = count + 1
    end
    return count
end

local file = io.open("./tests/Mocks/song.chart", "r")

if file then
    local content = file:read("*a")

    local value = rhythmgameutilities.read_time_signature_changes_from_chart_data(content);

    print(get_table_length(value)) -- 4
end
```
