#### `Utilities.RoundUpToTheNearestMultiplier`

> Languages: `C#` `C++` `GDScript` `JavaScript`

##### C#

```csharp
// Documentation/API/Utilities/RoundUpToTheNearestMultiplier.cs
using System;
using RhythmGameUtilities;

var value = Utilities.RoundUpToTheNearestMultiplier(12, 10);

Console.WriteLine(value); // 20
```

##### C++

```cpp
// Documentation/API/Utilities/RoundUpToTheNearestMultiplier.cpp
#include <iostream>

#include "RhythmGameUtilities/Utilities.hpp"

using namespace RhythmGameUtilities;

auto main() -> int
{
    auto value = RoundUpToTheNearestMultiplier(12, 10);

    std::cout << value << std::endl; // 20

    return 0;
}
```

##### GDScript

```gdscript
# Documentation/API/Utilities/RoundUpToTheNearestMultiplier.gd
extends Node

func _ready() -> void:
	var value: int = rhythm_game_utilities.round_up_to_the_nearest_multiplier(12, 10)

	print(value) # 20
```

##### JavaScript

```javascript
// Documentation/API/Utilities/RoundUpToTheNearestMultiplier.js
import RhythmGameUtilities from '@rhythm-game-utilities/core';

const value = RhythmGameUtilities.RoundUpToTheNearestMultiplier(12, 10);

console.log(value); // 20
```
