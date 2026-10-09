---@type RhythmGameUtilities
local rhythmgameutilities = require("rhythmgameutilities")

local value = rhythmgameutilities.lerp_unclamped(0, 10, 1.1);

print(tonumber(string.format("%i", value))) -- 11
