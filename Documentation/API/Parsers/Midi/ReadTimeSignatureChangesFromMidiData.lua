---@type RhythmGameUtilities
local rhythmgameutilities = require("rhythmgameutilities")

local function get_table_length(table)
    local count = 0
    for _ in pairs(table) do
        count = count + 1
    end
    return count
end

local file = io.open("./tests/Mocks/song.mid", "rb")

if file then
    local data = file:read("*a")

    local value = rhythmgameutilities.read_time_signature_changes_from_midi_data(data);

    print(get_table_length(value)) -- 1
end
