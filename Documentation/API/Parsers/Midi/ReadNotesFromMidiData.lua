---@type RhythmGameUtilities
local rhythmgameutilities = require("rhythmgameutilities")

local file = io.open("./tests/Mocks/song.mid", "rb")

if file then
    local data = file:read("*a")

    local notes = rhythmgameutilities.read_notes_from_midi_data(data);

    for _, note in pairs(notes) do
        print(note["position"] .. " " .. note["hand_position"])
    end
end
