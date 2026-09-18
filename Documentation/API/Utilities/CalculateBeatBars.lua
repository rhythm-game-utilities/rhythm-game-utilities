---@type RhythmGameUtilities
local rhythmgameutilities = require("rhythmgameutilities")

local function get_table_length(table)
    local count = 0
    if table ~= nil then
        for _ in pairs(table) do
            count = count + 1
        end
    end
    return count
end

local resolution = 192;

local tempo_changes = { { position = 0, bpm = 88000 }, { position = 3840, bpm = 112000 },
    { position = 9984, bpm = 89600 }, { position = 22272, bpm = 112000 },
    { position = 33792, bpm = 111500 }, { position = 34560, bpm = 112000 },
    { position = 42240, bpm = 111980 } };

local value = rhythmgameutilities.calculate_beat_bars(tempo_changes, resolution, true);

print(get_table_length(value)) -- 440
