---@type RhythmGameUtilities
local rhythmgameutilities = require("rhythmgameutilities")

local value = rhythmgameutilities.inverse_lerp(0, 10, 5);

print(tonumber(string.format("%.1f", value))) -- 0.5
