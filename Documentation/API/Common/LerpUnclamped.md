#### `Common.LerpUnclamped`

> Languages: `C#` `C++` `GDScript` `JavaScript` `Lua`

##### C#

```csharp
// Documentation/API/Common/LerpUnclamped.cs
using System;
using RhythmGameUtilities;

var value = Common.LerpUnclamped(0, 10, 1.1f);

Console.WriteLine(value); // 11
```

##### C++

```cpp
// Documentation/API/Common/LerpUnclamped.cpp
#include <iostream>

#include "RhythmGameUtilities/Common.hpp"

using namespace RhythmGameUtilities;

auto main() -> int
{
    auto value = LerpUnclamped(0, 10, 1.1f);

    std::cout << value << std::endl; // 11

    return 0;
}
```

##### GDScript

```gdscript
# Documentation/API/Common/LerpUnclamped.gd
extends Node

func _ready() -> void:
	var value: float = rhythm_game_utilities.lerp_unclamped(0, 10, 1.1)

	print(value) # 11
```

##### JavaScript

```javascript
// Documentation/API/Common/LerpUnclamped.js
import RhythmGameUtilities from '@rhythm-game-utilities/core';

const value = RhythmGameUtilities.LerpUnclamped(0, 10, 1.1);

console.log(value); // 11
```

##### Lua

```lua
-- Documentation/API/Common/LerpUnclamped.lua
---@type RhythmGameUtilities
local rhythmgameutilities = require("rhythmgameutilities")

local value = rhythmgameutilities.lerp_unclamped(0, 10, 1.1);

print(tonumber(string.format("%i", value))) -- 11
```
