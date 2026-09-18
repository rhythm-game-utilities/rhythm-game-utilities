---@type RhythmGameUtilities
local rhythmgameutilities = require("rhythmgameutilities")

local delta = 50;

local notes = { { id = 1, position = 768, hand_position = 0, length = 0 },
    { id = 2,  position = 960,  hand_position = 0, length = 0 },
    { id = 3,  position = 1152, hand_position = 0, length = 0 },
    { id = 4,  position = 1536, hand_position = 0, length = 0 },
    { id = 5,  position = 1728, hand_position = 0, length = 0 },
    { id = 6,  position = 1920, hand_position = 0, length = 0 },
    { id = 7,  position = 2304, hand_position = 0, length = 0 },
    { id = 8,  position = 2496, hand_position = 0, length = 0 },
    { id = 9,  position = 2688, hand_position = 0, length = 0 },
    { id = 10, position = 3072, hand_position = 0, length = 0 },
    { id = 11, position = 3264, hand_position = 0, length = 0 } };

local value = rhythmgameutilities.find_notes_near_given_tick(notes, 750, delta);

print(value[1].position) -- 768
