---@type RhythmGameUtilities
local rhythmgameutilities = require("rhythmgameutilities")

local value = rhythmgameutilities.is_on_the_beat(120, 10, 0.05);

print(value) -- true
