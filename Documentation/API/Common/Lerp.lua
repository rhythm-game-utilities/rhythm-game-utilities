---@type RhythmGameUtilities
local rhythmgameutilities = require("rhythmgameutilities")

local value = rhythmgameutilities.lerp(0, 10, 0.5);

print(tonumber(string.format("%i", value))) -- 5
