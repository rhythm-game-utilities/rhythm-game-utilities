---@type RhythmGameUtilities
local rhythmgameutilities = require("rhythmgameutilities")

local function get_table_length(table)
    local count = 0
    for _ in pairs(table) do
        count = count + 1
    end
    return count
end

local function inverse_lerp_test()
    local value = rhythmgameutilities.inverse_lerp(0, 10, 5);

    print(value) -- 0.5

    assert(value == 0.5)
end

local function inverse_lerp_unclamped_test()
    local value = rhythmgameutilities.inverse_lerp_unclamped(0, 10, 11);

    print(value) -- 1.1

    assert(math.abs(value - 1.1) < 0.0001)
end

local function lerp_test()
    local value = rhythmgameutilities.lerp(0, 10, 0.5);

    print(value) -- 5.0

    assert(value == 5)
end

local function read_resolution_from_chart_data_test()
    local file = io.open("../tests/Mocks/song.chart", "r")

    assert(file)

    local content = file:read("*a")

    local value = rhythmgameutilities.read_resolution_from_chart_data(content);

    print(value) -- 192

    assert(value == 192)
end

local function read_tempo_changes_from_chart_data_test()
    local file = io.open("../tests/Mocks/song.chart", "r")

    assert(file)

    local content = file:read("*a")

    local value = rhythmgameutilities.read_tempo_changes_from_chart_data(content);

    print(get_table_length(value)) -- 7

    assert(get_table_length(value) == 7)
end

local function read_time_signature_changes_from_chart_data_test()
    local file = io.open("../tests/Mocks/song.chart", "r")

    assert(file)

    local content = file:read("*a")

    local value = rhythmgameutilities.read_time_signature_changes_from_chart_data(content);

    print(get_table_length(value)) -- 4

    assert(get_table_length(value) == 4)
end

local function read_notes_from_chart_data_test()
    local file = io.open("../tests/Mocks/song.chart", "r")

    assert(file)

    local content = file:read("*a")

    local value = rhythmgameutilities.read_notes_from_chart_data(content, Difficulty.Easy);

    print(get_table_length(value)) -- 8

    assert(get_table_length(value) == 8)
end

local function calculate_accuracy_ratio_test()
    local value = rhythmgameutilities.calculate_accuracy_ratio(750, 768, 50);

    value = tonumber(string.format("%.2f", value));

    print(value) -- 0.64

    assert(value == value)
end

local function convert_tick_to_position_test()
    local value = rhythmgameutilities.convert_tick_to_position(1056, 192);

    print(value) -- 5.5

    assert(value == 5.5)
end

local function is_on_the_beat_test()
    local value = rhythmgameutilities.is_on_the_beat(120, 10, 0.05);

    print(value) -- true

    assert(value == true)
end

local function round_up_to_the_nearest_multiplier_test()
    local value = rhythmgameutilities.round_up_to_the_nearest_multiplier(12, 10);

    print(value) -- 20

    assert(value == 20)
end

inverse_lerp_test();
inverse_lerp_unclamped_test();
lerp_test();

read_resolution_from_chart_data_test();
read_tempo_changes_from_chart_data_test();
read_time_signature_changes_from_chart_data_test();
read_notes_from_chart_data_test();

calculate_accuracy_ratio_test();
convert_tick_to_position_test();

is_on_the_beat_test();
round_up_to_the_nearest_multiplier_test();
