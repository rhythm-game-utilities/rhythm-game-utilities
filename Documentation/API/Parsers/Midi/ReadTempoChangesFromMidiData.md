#### `Midi.ReadTempoChangesFromMidiData`

> Languages: `C#` `C++` `GDScript` `JavaScript` `Lua`

##### C#

```csharp
// Documentation/API/Parsers/Midi/ReadTempoChangesFromMidiData.cs
using System;
using System.IO;
using RhythmGameUtilities;

var bytes = File.ReadAllBytes("./tests/Mocks/song.mid");

var tempoChanges = Midi.ReadTempoChangesFromMidiData(bytes);

Console.WriteLine(tempoChanges.Length); // 1
```

##### C++

```cpp
// Documentation/API/Parsers/Midi/ReadTempoChangesFromMidiData.cpp
#include <iostream>

#include "RhythmGameUtilities/File.hpp"
#include "RhythmGameUtilities/Parsers/Midi.hpp"

using namespace RhythmGameUtilities;

auto main() -> int
{
    auto bytes = ReadBytesFromFile("./tests/Mocks/song.mid");

    auto tempoChanges = ReadTempoChangesFromMidiData(bytes);

    std::cout << size(tempoChanges) << std::endl; // 7

    return 0;
}
```

##### GDScript

```gdscript
# Documentation/API/Parsers/Midi/ReadTempoChangesFromMidiData.gd
extends Node

func _ready() -> void:
	var file: FileAccess = FileAccess.open("res://song.mid", FileAccess.READ)
	var bytes: PackedByteArray = file.get_buffer(file.get_length())

	var tempo_changes: Array = rhythm_game_utilities.read_tempo_changes_from_midi_data(bytes)

	print(tempo_changes)
```

##### JavaScript

```javascript
// Documentation/API/Parsers/Midi/ReadTempoChangesFromMidiData.js
import { readFileSync } from 'node:fs';

import RhythmGameUtilities from '@rhythm-game-utilities/core';

const data = readFileSync('./tests/Mocks/song.mid');

const tempoChanges = RhythmGameUtilities.ReadTempoChangesFromMidiData(data);

console.log(tempoChanges.length); // 1
```

##### Lua

```lua
-- Documentation/API/Parsers/Midi/ReadTempoChangesFromMidiData.lua
---@type RhythmGameUtilities
local rhythmgameutilities = require("rhythmgameutilities")

local function get_table_length(table)
    local count = 0
    for _ in pairs(table) do
        count = count + 1
    end
    return count
end

local file = io.open("./tests/Mocks/song.mid", "rb")

if file then
    local data = file:read("*a")

    local value = rhythmgameutilities.read_tempo_changes_from_midi_data(data);

    print(get_table_length(value)) -- 1
end
```
