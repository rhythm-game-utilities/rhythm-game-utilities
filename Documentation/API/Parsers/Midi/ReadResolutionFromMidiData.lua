---@type RhythmGameUtilities
local rhythmgameutilities = require("rhythmgameutilities")

local file = io.open("./tests/Mocks/song.mid", "rb")

if file then
    local data = file:read("*a")

    local value = rhythmgameutilities.read_resolution_from_midi_data(data);

    print(value) -- 480
end
