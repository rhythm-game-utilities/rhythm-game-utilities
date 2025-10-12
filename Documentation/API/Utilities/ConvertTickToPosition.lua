---@type RhythmGameUtilities
local rhythmgameutilities = require("rhythmgameutilities")

local tick = 1056;
local resolution = 192;

local value = rhythmgameutilities.convert_tick_to_position(tick, resolution);

print(value) -- 5.5
