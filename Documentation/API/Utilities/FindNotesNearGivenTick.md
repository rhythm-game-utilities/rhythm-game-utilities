#### `Utilities.FindNotesNearGivenTick`

> Languages: `C#` `C++` `GDScript`

##### C#

```csharp
// Documentation/API/Utilities/FindNotesNearGivenTick.cs
using System;
using RhythmGameUtilities;

var notes = new Note[]
{
    new() { ID = 1, Position = 768 }, new() { ID = 2, Position = 960 },
    new() { ID = 3, Position = 1152 }, new() { ID = 4, Position = 1536 },
    new() { ID = 5, Position = 1728 }, new() { ID = 6,  Position = 1920 },
    new() { ID = 7, Position = 2304 }, new() { ID = 8, Position = 2496 },
    new() { ID = 9, Position = 2688 }, new() { ID = 10, Position = 3072 },
    new() { ID = 11, Position = 3264 }
};

var foundNotes = Utilities.FindNotesNearGivenTick(notes, 750);

if (foundNotes?.Length > 0)
{
    Console.Write(foundNotes[0].Position); // 768
}
```

##### C++

```cpp
// Documentation/API/Utilities/FindNotesNearGivenTick.cpp
#include <iostream>

#include "RhythmGameUtilities/Utilities.hpp"

using namespace RhythmGameUtilities;

auto main() -> int
{
    std::vector<Note> notes = {
        {1, 768, 0, 0},  {2, 960, 0, 0},   {3, 1152, 0, 0}, {4, 1536, 0, 0},
        {5, 1728, 0, 0}, {6, 1920, 0, 0},  {7, 2304, 0, 0}, {8, 2496, 0, 0},
        {9, 2688, 0, 0}, {10, 3072, 0, 0}, {11, 3264, 0, 0}};

    auto foundNotes = FindNotesNearGivenTick(notes, 750);

    if (size(foundNotes) > 0)
    {
        std::cout << foundNotes[0].Position << std::endl; // 768
    }

    return 0;
}
```

##### GDScript

```gdscript
extends Node

func _ready() -> void:
	var delta: int = 50

	var notes: Array = [
		{"position": 768}, {"position": 960}, {"position": 1152},
		{"position": 1536}, {"position": 1728}, {"position": 1920},
		{"position": 2304}, {"position": 2496}, {"position": 2688},
		{"position": 3072}, {"position": 3264}
	]

	var found_notes: Array = rhythm_game_utilities.find_notes_near_given_tick(notes, 750, delta);

	print(found_notes[0]["position"]) # 768
```
