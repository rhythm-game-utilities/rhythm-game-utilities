#### `Utilities.ConvertTickToPosition`

> Languages: `C#` `C++` `GDScript` `JavaScript`

##### C#

```csharp
// Documentation/API/Utilities/ConvertTickToPosition.cs
using System;
using RhythmGameUtilities;

const int tick = 1056;
const int resolution = 192;

var position = Utilities.ConvertTickToPosition(tick, resolution);

Console.WriteLine(position); // 5.5
```

##### C++

```cpp
// Documentation/API/Utilities/ConvertTickToPosition.cpp
#include <iostream>

#include "RhythmGameUtilities/Utilities.hpp"

using namespace RhythmGameUtilities;

auto main() -> int
{
    const int tick = 1056;
    const int resolution = 192;

    auto position = ConvertTickToPosition(tick, resolution);

    std::cout << position << std::endl; // 5.5

    return 0;
}
```

##### GDScript

```gdscript
# Documentation/API/Utilities/ConvertTickToPosition.gd
extends Node

func _ready() -> void:
	var tick: int = 1056
	var resolution: int = 192

	var position: float = rhythm_game_utilities.convert_tick_to_position(tick, resolution)

	print(position) # 5.5
```

##### JavaScript

```javascript
// Documentation/API/Utilities/ConvertTickToPosition.js
import RhythmGameUtilities from '@rhythm-game-utilities/core';

const tick = 1056;
const resolution = 192;

const position = RhythmGameUtilities.ConvertTickToPosition(tick, resolution);

console.log(position); // 5.5
```
