---@type RhythmGameUtilities
local rhythmgameutilities = require("rhythmgameutilities")

local function get_table_length(table)
    local count = 0
    for _ in pairs(table) do
        count = count + 1
    end
    return count
end

local file = io.open("../tests/Mocks/song.chart", "r")

if file then
    local content = file:read("*a")

    local value = rhythmgameutilities.read_tempo_changes_from_chart_data(content);

    print(get_table_length(value))
end
