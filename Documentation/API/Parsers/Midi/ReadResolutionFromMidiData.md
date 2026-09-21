#### `Midi.ReadResolutionFromMidiData`

> Languages: `C#` `C++` `GDScript` `JavaScript`

##### C#

```csharp
// Documentation/API/Parsers/Midi/ReadResolutionFromMidiData.cs
using System;
using System.IO;
using RhythmGameUtilities;

var bytes = File.ReadAllBytes("./tests/Mocks/song.mid");

var resolution = Midi.ReadResolutionFromMidiData(bytes);

Console.WriteLine(resolution); // 480
```

##### C++

```cpp
// Documentation/API/Parsers/Midi/ReadResolutionFromMidiData.cpp
#include <iostream>

#include "RhythmGameUtilities/File.hpp"
#include "RhythmGameUtilities/Parsers/Midi.hpp"

using namespace RhythmGameUtilities;

auto main() -> int
{
    auto bytes = ReadBytesFromFile("./tests/Mocks/song.mid");

    auto resolution = ReadResolutionFromMidiData(bytes);

    std::cout << resolution << std::endl;

    return 0;
}
```

##### GDScript

```gdscript
# Documentation/API/Parsers/Midi/ReadResolutionFromMidiData.gd
extends Node

func _ready() -> void:
	var file: FileAccess = FileAccess.open("res://song.mid", FileAccess.READ)
	var bytes: PackedByteArray = file.get_buffer(file.get_length())

	var resolution: int = rhythm_game_utilities.read_resolution_from_midi_data(bytes)

	print(resolution)
```

##### JavaScript

```javascript
// Documentation/API/Parsers/Midi/ReadResolutionFromMidiData.js
import { readFileSync } from 'node:fs';

import RhythmGameUtilities from '@rhythm-game-utilities/core';

const data = readFileSync('./tests/Mocks/song.mid');

const resolution = RhythmGameUtilities.ReadResolutionFromMidiData(data);

console.log(resolution); // 480
```
