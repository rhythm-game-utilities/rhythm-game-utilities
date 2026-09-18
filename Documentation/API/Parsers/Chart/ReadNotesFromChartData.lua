---@type RhythmGameUtilities
local rhythmgameutilities = require("rhythmgameutilities")

local file = io.open("./tests/Mocks/song.chart", "r")

if file then
    local content = file:read("*a")

    local notes = rhythmgameutilities.read_notes_from_chart_data(content, Difficulty.Expert);

    for _, note in pairs(notes) do
        print(note["position"] .. " " .. note["hand_position"])
    end
end
