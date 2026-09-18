---@type RhythmGameUtilities
local rhythmgameutilities = require("rhythmgameutilities")

local value = rhythmgameutilities.inverse_lerp_unclamped(0, 10, 11);

print(tonumber(string.format("%.1f", value))) -- 1.1
