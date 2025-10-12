---@type RhythmGameUtilities
local rhythmgameutilities = require("rhythmgameutilities")

local seconds = 2;
local resolution = 192;
local position_delta = 50;

local tempo_changes = { { position = 0, bpm = 120000 } };

local current_position =
    rhythmgameutilities.convert_seconds_to_ticks(seconds, resolution, tempo_changes);

local value = rhythmgameutilities.calculate_accuracy_ratio(750, current_position, position_delta);

print(string.format("%.2f", value)) -- -0.36
