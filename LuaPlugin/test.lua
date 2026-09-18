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

    local value = rhythmgameutilities.read_notes_from_chart_data(content, Difficulty.Expert);

    print(get_table_length(value)) -- 8

    assert(get_table_length(value) == 8)
end

local function convert_seconds_to_ticks_test()
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

    local value = rhythmgameutilities.convert_seconds_to_ticks(seconds, resolution, tempo_changes);

    print(value) -- 1408

    assert(value == 1408)
end

local function calculate_beat_bars_test()
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

    local value = rhythmgameutilities.calculate_beat_bars(tempo_changes, resolution, true);

    print(get_table_length(value)) -- 440

    assert(get_table_length(value) == 440)
end

local function find_notes_near_given_tick_test()
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

    local value = rhythmgameutilities.find_notes_near_given_tick(notes, 750, 50);

    assert(value[1].position == 768)
end

local function calculate_accuracy_ratio_test()
    local seconds = 2;
    local resolution = 192;
    local delta = 50;

    local tempo_changes = { { position = 0, bpm = 120000 } };

    local current_position =
        rhythmgameutilities.convert_seconds_to_ticks(seconds, resolution, tempo_changes);

    local value = rhythmgameutilities.calculate_accuracy_ratio(750, current_position, delta);

    print(value) -- -0.36

    value = tonumber(string.format("%.2f", value));

    assert(value == -0.36)
end

local function calculate_accuracy_test()
    local seconds = 2;
    local resolution = 192;
    local delta = 50;

    local tempo_changes = { { position = 0, bpm = 120000 } };

    local current_position =
        rhythmgameutilities.convert_seconds_to_ticks(seconds, resolution, tempo_changes);

    local value = rhythmgameutilities.calculate_accuracy(750, current_position, delta);

    print(value) -- Good

    assert(value == "Good")
end

local function calculate_timing_test()
    local seconds = 2;
    local resolution = 192;
    local delta = 50;

    local tempo_changes = { { position = 0, bpm = 120000 } };

    local current_position =
        rhythmgameutilities.convert_seconds_to_ticks(seconds, resolution, tempo_changes);

    local value = rhythmgameutilities.calculate_timing(750, current_position, delta);

    print(value) -- Hit

    assert(value == "Hit")
end

local function convert_tick_to_position_test()
    local tick = 1056;
    local resolution = 192;

    local value = rhythmgameutilities.convert_tick_to_position(tick, resolution);

    print(value) -- 5.5

    assert(value == 5.5)
end

local function is_on_the_beat_test()
    local bpm = 120;
    local current_time = 10;
    local delta = 0.05;

    local value = rhythmgameutilities.is_on_the_beat(bpm, current_time, delta);

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

convert_seconds_to_ticks_test();
calculate_beat_bars_test();
find_notes_near_given_tick_test();
calculate_accuracy_ratio_test();
calculate_accuracy_test();
calculate_timing_test();
convert_tick_to_position_test();
is_on_the_beat_test();
round_up_to_the_nearest_multiplier_test();
