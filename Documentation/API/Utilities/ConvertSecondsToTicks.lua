---@type RhythmGameUtilities
local rhythmgameutilities = require("rhythmgameutilities")

local seconds = 5;
local resolution = 192;

local tempo_changes = {
    { position = 0,     bpm = 88000 },
    { position = 3840,  bpm = 112000 },
    { position = 9984,  bpm = 89600 },
    { position = 22272, bpm = 112000 },
    { position = 33792, bpm = 111500 },
    { position = 34560, bpm = 112000 },
    { position = 42240, bpm = 111980 }
}

local ticks =
    rhythmgameutilities.convert_seconds_to_ticks(seconds, resolution, tempo_changes);

print(ticks); --1408
