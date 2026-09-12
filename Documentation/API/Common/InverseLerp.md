#### `Common.InverseLerp`

> Languages: `C#` `C++` `GDScript`

##### C#

```csharp
// Documentation/API/Common/InverseLerp.cs
using System;
using RhythmGameUtilities;

var value = Common.InverseLerp(0, 10, 5);

Console.WriteLine(value); // 0.5
```

##### C++

```cpp
// Documentation/API/Common/InverseLerp.cpp
#include <iostream>

#include "RhythmGameUtilities/Common.hpp"

using namespace RhythmGameUtilities;

auto main() -> int
{
    auto value = InverseLerp(0, 10, 5);

    std::cout << value << std::endl; // 0.5

    return 0;
}
```

##### GDScript

```gdscript
# Documentation/API/Common/InverseLerp.gd
extends Node

func _ready() -> void:
	var value: float = rhythm_game_utilities.inverse_lerp(0, 10, 5)

	print(value) # 0.5
```

##### JavaScript

```javascript
// Documentation/API/Common/InverseLerp.js
import RhythmGameUtilities from '@rhythm-game-utilities/core';

const value = RhythmGameUtilities.InverseLerp(0, 10, 5);

console.log(value); // 0.5
```
