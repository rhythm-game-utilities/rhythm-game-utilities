#### `Chart.ReadResolutionFromChartData`

> Languages: `C#` `C++` `GDScript`

##### C#

```csharp
// Documentation/API/Parsers/Chart/ReadResolutionFromChartData.cs
using System;
using System.IO;
using RhythmGameUtilities;

var contents = File.ReadAllText("./song.chart");

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
    auto contents = ReadStringFromFile("./song.chart");

    auto resolution = ReadResolutionFromChartData(contents.c_str());

    std::cout << resolution << std::endl;

    return 0;
}
```

##### GDScript

```gdscript
extends Node

func _ready() -> void:
	var file: FileAccess = FileAccess.open("res://song.chart", FileAccess.READ)
	var contents: String = file.get_as_text()

	var resolution: int = rhythm_game_utilities.read_resolution_from_chart_data(contents)

	print(resolution)
```

##### Lua

```lua
-- Documentation/API/Parsers/Chart/ReadResolutionFromChartData.lua
---@type RhythmGameUtilities
local rhythmgameutilities = require("rhythmgameutilities")

local file = io.open("../tests/Mocks/song.chart", "r")

if file then
    local content = file:read("*a")

    local value = rhythmgameutilities.read_resolution_from_chart_data(content);

    print(value) -- 192
end
```
