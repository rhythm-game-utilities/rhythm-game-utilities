#### `Common.InverseLerpUnclamped`

> Languages: `C#` `C++` `GDScript` `JavaScript` `Lua`

##### C#

```csharp
// Documentation/API/Common/InverseLerpUnclamped.cs
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
# Documentation/API/Common/InverseLerpUnclamped.gd
extends Node

func _ready() -> void:
	var value: float = rhythm_game_utilities.inverse_lerp_unclamped(0, 10, 11)

	print(value) # 1.1
```

##### JavaScript

```javascript
// Documentation/API/Common/InverseLerpUnclamped.js
import RhythmGameUtilities from '@rhythm-game-utilities/core';

const value = RhythmGameUtilities.InverseLerpUnclamped(0, 10, 11);

console.log(value.toFixed(1)); // 1.1
```

##### Lua

```lua
-- Documentation/API/Common/InverseLerpUnclamped.lua
---@type RhythmGameUtilities
local rhythmgameutilities = require("rhythmgameutilities")

local value = rhythmgameutilities.inverse_lerp_unclamped(0, 10, 11);

print(tonumber(string.format("%.1f", value))) -- 1.1
```
