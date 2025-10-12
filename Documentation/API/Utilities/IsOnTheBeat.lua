---@type RhythmGameUtilities
local rhythmgameutilities = require("rhythmgameutilities")

local bpm = 120;
local current_time = 10;
local delta = 0.05;

local isOnTheBeat = rhythmgameutilities.is_on_the_beat(bpm, current_time, delta);

if isOnTheBeat then
    print("Is on the beat!") -- Is on the beat!
else
    print("Is not on the beat!")
end
