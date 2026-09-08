---@type RhythmGameUtilities
local rhythmgameutilities = require("rhythmgameutilities")

local value = rhythmgameutilities.calculate_accuracy_ratio(750, 768, 50);

value = tonumber(string.format("%.2f", value));

print(value) -- 0.64
