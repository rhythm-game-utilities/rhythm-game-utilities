#### `Common.InverseLerpUnclamped`

> Languages: `C#` `C++` `GDScript`

##### C#

```csharp
using System;
using RhythmGameUtilities;

var value = Common.InverseLerpUnclamped(0, 10, 11);

Console.WriteLine(value); // 1.1
```

##### C++

```cpp
// Documentation/API/Common/InverseLerpUnclamped.cpp
#include <iostream>

#include "RhythmGameUtilities/Common.hpp"

using namespace RhythmGameUtilities;

auto main() -> int
{
    auto value = InverseLerpUnclamped(0, 10, 11);

    std::cout << value << std::endl; // 1.1

    return 0;
}
```

##### GDScript

```gdscript
extends Node

func _ready() -> void:
	var value: float = rhythm_game_utilities.inverse_lerp_unclamped(0, 10, 11)

	print(value) # 1.1
```
