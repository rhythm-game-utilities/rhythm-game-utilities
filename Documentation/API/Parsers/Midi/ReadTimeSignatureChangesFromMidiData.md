#### `Midi.ReadTimeSignatureChangesFromMidiData`

> Languages: `C#` `C++` `GDScript` `JavaScript`

##### C#

```csharp
// Documentation/API/Parsers/Midi/ReadTimeSignatureChangesFromMidiData.cs
using System;
using System.IO;
using RhythmGameUtilities;

var bytes = File.ReadAllBytes("./tests/Mocks/song.mid");

var timeSignatureChanges = Midi.ReadTimeSignatureChangesFromMidiData(bytes);

Console.WriteLine(timeSignatureChanges.Length); // 1
```

##### C++

```cpp
// Documentation/API/Parsers/Midi/ReadTimeSignatureChangesFromMidiData.cpp
#include <iostream>

#include "RhythmGameUtilities/File.hpp"
#include "RhythmGameUtilities/Parsers/Midi.hpp"

using namespace RhythmGameUtilities;

auto main() -> int
{
    auto bytes = ReadBytesFromFile("./tests/Mocks/song.mid");

    auto timeSignatureChanges = ReadTimeSignatureChangesFromMidiData(bytes);

    std::cout << size(timeSignatureChanges) << std::endl; // 4

    return 0;
}
```

##### GDScript

```gdscript
# Documentation/API/Parsers/Midi/ReadTimeSignatureChangesFromMidiData.gd
extends Node

func _ready() -> void:
	var file: FileAccess = FileAccess.open("res://song.mid", FileAccess.READ)
	var bytes: PackedByteArray = file.get_buffer(file.get_length())

	var time_signature_changes: Array = rhythm_game_utilities.read_time_signature_changes_from_midi_data(bytes)

	print(time_signature_changes)
```

##### JavaScript

```javascript
// Documentation/API/Parsers/Midi/ReadTimeSignatureChangesFromMidiData.js
import { readFileSync } from 'node:fs';

import RhythmGameUtilities from '@rhythm-game-utilities/core';

const data = readFileSync('./tests/Mocks/song.mid');

const timeSignatureChanges =
  RhythmGameUtilities.ReadTimeSignatureChangesFromMidiData(data);

console.log(timeSignatureChanges.length); // 1
```
