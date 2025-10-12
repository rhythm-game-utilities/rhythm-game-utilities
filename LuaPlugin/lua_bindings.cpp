#include "RhythmGameUtilities/Common.hpp"
#include "RhythmGameUtilities/Enums/Accuracy.hpp"
#include "RhythmGameUtilities/Enums/Difficulty.hpp"
#include "RhythmGameUtilities/Enums/Timing.hpp"
#include "RhythmGameUtilities/Parsers/Chart.hpp"
#include "RhythmGameUtilities/Structs/BeatBar.hpp"
#include "RhythmGameUtilities/Structs/Tempo.hpp"
#include "RhythmGameUtilities/Structs/TimeSignature.hpp"
#include "RhythmGameUtilities/Utilities.hpp"

#include <luajit-2.1/lua.hpp>

// Lua Helpers

static auto lua_get_tempo_changes_from_attribute(lua_State *L, int idx)
    -> std::vector<RhythmGameUtilities::Tempo>
{
    luaL_checktype(L, idx, LUA_TTABLE);

    std::vector<RhythmGameUtilities::Tempo> tempo_changes;
    size_t length = lua_objlen(L, idx);
    tempo_changes.reserve(length);

    for (auto i = 1; i <= length; i += 1)
    {
        lua_rawgeti(L, idx, i);

        if (lua_istable(L, -1))
        {
            lua_getfield(L, -1, "position");
            auto position = static_cast<int>(luaL_checknumber(L, -1));
            lua_pop(L, 1);

            lua_getfield(L, -1, "bpm");
            auto bpm = static_cast<int>(luaL_checknumber(L, -1));
            lua_pop(L, 1);

            tempo_changes.emplace_back(position, bpm);
        }
        lua_pop(L, 1);
    }

    return tempo_changes;
}

static auto lua_get_notes_from_attribute(lua_State *L, int idx)
    -> std::vector<RhythmGameUtilities::Note>
{
    luaL_checktype(L, idx, LUA_TTABLE);

    std::vector<RhythmGameUtilities::Note> notes;
    size_t length = lua_objlen(L, idx);
    notes.reserve(length);

    for (auto i = 1; i <= length; i += 1)
    {
        lua_rawgeti(L, idx, i);

        if (lua_istable(L, -1))
        {
            lua_getfield(L, -1, "id");
            auto id = static_cast<int>(luaL_checknumber(L, -1));
            lua_pop(L, 1);

            lua_getfield(L, -1, "position");
            auto position = static_cast<int>(luaL_checknumber(L, -1));
            lua_pop(L, 1);

            lua_getfield(L, -1, "hand_position");
            auto hand_position = static_cast<int>(luaL_checknumber(L, -1));
            lua_pop(L, 1);

            lua_getfield(L, -1, "length");
            auto length = static_cast<int>(luaL_checknumber(L, -1));
            lua_pop(L, 1);

            notes.emplace_back(id, position, hand_position, length);
        }
        lua_pop(L, 1);
    }

    return notes;
}

static auto
lua_return_beat_bars(lua_State *L,
                     const std::vector<RhythmGameUtilities::BeatBar> &beat_bars)
    -> void
{
    lua_createtable(L, static_cast<int>(beat_bars.size()), 0);

    for (auto i = 0; i < beat_bars.size(); i += 1)
    {
        lua_createtable(L, 0, 2);

        lua_pushinteger(L, beat_bars[i].Position);
        lua_setfield(L, -2, "position");

        lua_pushinteger(L, beat_bars[i].BPM);
        lua_setfield(L, -2, "bpm");

        lua_rawseti(L, -2, static_cast<lua_Integer>(i + 1));
    }
}

static auto lua_return_notes_table(
    lua_State *L, const std::vector<RhythmGameUtilities::Note> &notes) -> void
{
    lua_createtable(L, static_cast<int>(notes.size()), 0);

    for (auto i = 0; i < notes.size(); i += 1)
    {
        lua_createtable(L, 0, 4);

        lua_pushinteger(L, notes[i].ID);
        lua_setfield(L, -2, "id");

        lua_pushinteger(L, notes[i].Position);
        lua_setfield(L, -2, "position");

        lua_pushinteger(L, notes[i].HandPosition);
        lua_setfield(L, -2, "hand_position");

        lua_pushinteger(L, notes[i].Length);
        lua_setfield(L, -2, "length");

        lua_rawseti(L, -2, static_cast<lua_Integer>(i + 1));
    }
}

static auto lua_return_tempo_changes_table(
    lua_State *L, const std::vector<RhythmGameUtilities::Tempo> &tempo_changes)
    -> void
{
    lua_createtable(L, static_cast<int>(tempo_changes.size()), 0);

    for (auto i = 0; i < tempo_changes.size(); i += 1)
    {
        lua_createtable(L, 0, 2);

        lua_pushinteger(L, tempo_changes[i].Position);
        lua_setfield(L, -2, "position");

        lua_pushinteger(L, tempo_changes[i].BPM);
        lua_setfield(L, -2, "bpm");

        lua_rawseti(L, -2, static_cast<lua_Integer>(i + 1));
    }
}

static auto lua_return_time_signature_table(
    lua_State *L,
    const std::vector<RhythmGameUtilities::TimeSignature> &time_signature)
    -> void
{
    lua_createtable(L, static_cast<int>(time_signature.size()), 0);

    for (auto i = 0; i < time_signature.size(); i += 1)
    {
        lua_createtable(L, 0, 3);

        lua_pushinteger(L, time_signature[i].Position);
        lua_setfield(L, -2, "position");

        lua_pushinteger(L, time_signature[i].Numerator);
        lua_setfield(L, -2, "numerator");

        lua_pushinteger(L, time_signature[i].Denominator);
        lua_setfield(L, -2, "denominator");

        lua_rawseti(L, -2, static_cast<lua_Integer>(i + 1));
    }
}

// Enums

static void register_accuracy_enum(lua_State *L)
{
    lua_newtable(L);

    lua_pushinteger(
        L, static_cast<lua_Integer>(RhythmGameUtilities::Accuracy::Invalid));
    lua_setfield(L, -2, "Invalid");

    lua_pushinteger(
        L, static_cast<lua_Integer>(RhythmGameUtilities::Accuracy::Poor));
    lua_setfield(L, -2, "Poor");

    lua_pushinteger(
        L, static_cast<lua_Integer>(RhythmGameUtilities::Accuracy::Fair));
    lua_setfield(L, -2, "Fair");

    lua_pushinteger(
        L, static_cast<lua_Integer>(RhythmGameUtilities::Accuracy::Good));
    lua_setfield(L, -2, "Good");

    lua_pushinteger(
        L, static_cast<lua_Integer>(RhythmGameUtilities::Accuracy::Great));
    lua_setfield(L, -2, "Great");

    lua_pushinteger(
        L, static_cast<lua_Integer>(RhythmGameUtilities::Accuracy::Perfect));
    lua_setfield(L, -2, "Perfect");

    lua_setglobal(L, "Accuracy");
}

static void register_difficulty_enum(lua_State *L)
{
    lua_newtable(L);

    lua_pushinteger(
        L, static_cast<lua_Integer>(RhythmGameUtilities::Difficulty::Easy));
    lua_setfield(L, -2, "Easy");

    lua_pushinteger(
        L, static_cast<lua_Integer>(RhythmGameUtilities::Difficulty::Medium));
    lua_setfield(L, -2, "Medium");

    lua_pushinteger(
        L, static_cast<lua_Integer>(RhythmGameUtilities::Difficulty::Hard));
    lua_setfield(L, -2, "Hard");

    lua_pushinteger(
        L, static_cast<lua_Integer>(RhythmGameUtilities::Difficulty::Expert));
    lua_setfield(L, -2, "Expert");

    lua_setglobal(L, "Difficulty");
}

static void register_timing_enum(lua_State *L)
{
    lua_newtable(L);

    lua_pushinteger(
        L, static_cast<lua_Integer>(RhythmGameUtilities::Timing::Miss));
    lua_setfield(L, -2, "Miss");

    lua_pushinteger(L,
                    static_cast<lua_Integer>(RhythmGameUtilities::Timing::Hit));
    lua_setfield(L, -2, "Hit");

    lua_pushinteger(
        L, static_cast<lua_Integer>(RhythmGameUtilities::Timing::Early));
    lua_setfield(L, -2, "Early");

    lua_pushinteger(
        L, static_cast<lua_Integer>(RhythmGameUtilities::Timing::Late));
    lua_setfield(L, -2, "Late");

    lua_setglobal(L, "Timing");
}

// Common

static auto lua_inverse_lerp(lua_State *L) -> int
{
    auto a = static_cast<float>(luaL_checknumber(L, 1));
    auto b = static_cast<float>(luaL_checknumber(L, 2));
    auto v = static_cast<float>(luaL_checknumber(L, 3));

    auto result = RhythmGameUtilities::InverseLerp(a, b, v);

    lua_pushnumber(L, result);

    return 1;
}

static auto lua_inverse_lerp_unclamped(lua_State *L) -> int
{
    auto a = static_cast<float>(luaL_checknumber(L, 1));
    auto b = static_cast<float>(luaL_checknumber(L, 2));
    auto v = static_cast<float>(luaL_checknumber(L, 3));

    auto result = RhythmGameUtilities::InverseLerpUnclamped(a, b, v);

    lua_pushnumber(L, result);

    return 1;
}

static auto lua_lerp(lua_State *L) -> int
{
    auto a = static_cast<float>(luaL_checknumber(L, 1));
    auto b = static_cast<float>(luaL_checknumber(L, 2));
    auto t = static_cast<float>(luaL_checknumber(L, 3));

    auto result = RhythmGameUtilities::Lerp(a, b, t);

    lua_pushnumber(L, result);

    return 1;
}

// Chart

static auto lua_read_resolution_from_chart_data(lua_State *L) -> int
{
    std::string contents = luaL_checkstring(L, 1);

    auto result =
        RhythmGameUtilities::ReadResolutionFromChartData(contents.c_str());

    lua_pushinteger(L, result);

    return 1;
}

static auto lua_read_tempo_changes_from_chart_data(lua_State *L) -> int
{
    std::string contents = luaL_checkstring(L, 1);

    auto result = RhythmGameUtilities::ReadTempoChangesFromChartData(contents);

    lua_return_tempo_changes_table(L, result);

    return 1;
}

static auto lua_read_time_signature_changes_from_chart_data(lua_State *L) -> int
{
    std::string contents = luaL_checkstring(L, 1);

    auto result =
        RhythmGameUtilities::ReadTimeSignatureChangesFromChartData(contents);

    lua_return_time_signature_table(L, result);

    return 1;
}

static auto lua_read_notes_from_chart_data(lua_State *L) -> int
{
    std::string contents = luaL_checkstring(L, 1);

    auto difficulty = static_cast<RhythmGameUtilities::Difficulty>(
        static_cast<int>(luaL_checkinteger(L, 2)));

    auto result =
        RhythmGameUtilities::ReadNotesFromChartData(contents, difficulty);

    lua_return_notes_table(L, result);

    return 1;
}

// Utilities

static auto lua_convert_seconds_to_ticks(lua_State *L) -> int
{
    auto seconds = static_cast<float>(luaL_checknumber(L, 1));
    auto resolution = static_cast<int>(luaL_checkinteger(L, 2));

    auto tempo_changes = lua_get_tempo_changes_from_attribute(L, 3);

    auto result = RhythmGameUtilities::ConvertSecondsToTicks(
        seconds, resolution, tempo_changes);

    lua_pushinteger(L, result);

    return 1;
}

static auto lua_calculate_beat_bars(lua_State *L) -> int
{
    auto tempo_changes = lua_get_tempo_changes_from_attribute(L, 1);

    auto resolution = static_cast<int>(luaL_checkinteger(L, 2));
    auto include_half_notes = static_cast<bool>(lua_toboolean(L, 3));

    auto result = RhythmGameUtilities::CalculateBeatBars(
        tempo_changes, resolution, include_half_notes);

    lua_return_beat_bars(L, result);

    return 1;
}

static auto lua_find_notes_near_given_tick(lua_State *L) -> int
{
    auto notes = lua_get_notes_from_attribute(L, 1);

    auto tick = static_cast<int>(luaL_checkinteger(L, 2));
    auto delta = static_cast<int>(luaL_checkinteger(L, 3));

    auto result =
        RhythmGameUtilities::FindNotesNearGivenTick(notes, tick, delta);

    lua_return_notes_table(L, result);

    return 1;
}

static auto lua_calculate_accuracy_ratio(lua_State *L) -> int
{
    auto position = static_cast<int>(luaL_checkinteger(L, 1));
    auto current_position = static_cast<int>(luaL_checkinteger(L, 2));
    auto delta = static_cast<int>(luaL_checkinteger(L, 3));

    auto result = RhythmGameUtilities::CalculateAccuracyRatio(
        position, current_position, delta);

    lua_pushnumber(L, result);

    return 1;
}

static auto lua_calculate_accuracy(lua_State *L) -> int
{
    auto position = static_cast<int>(luaL_checkinteger(L, 1));
    auto current_position = static_cast<int>(luaL_checkinteger(L, 2));
    auto delta = static_cast<int>(luaL_checkinteger(L, 3));

    auto result = RhythmGameUtilities::CalculateAccuracy(
        position, current_position, delta);

    lua_pushstring(L, ToString(result).c_str());

    return 1;
}

static auto lua_calculate_timing(lua_State *L) -> int
{
    auto position = static_cast<int>(luaL_checkinteger(L, 1));
    auto current_position = static_cast<int>(luaL_checkinteger(L, 2));
    auto delta = static_cast<int>(luaL_checkinteger(L, 3));

    auto result =
        RhythmGameUtilities::CalculateTiming(position, current_position, delta);

    lua_pushstring(L, ToString(result).c_str());

    return 1;
}

static auto lua_convert_tick_to_position(lua_State *L) -> int
{
    auto tick = static_cast<int>(luaL_checkinteger(L, 1));
    auto resolution = static_cast<int>(luaL_checkinteger(L, 2));

    auto result = RhythmGameUtilities::ConvertTickToPosition(tick, resolution);

    lua_pushnumber(L, result);

    return 1;
}

static auto lua_is_on_the_beat(lua_State *L) -> int
{
    auto bpm = static_cast<int>(luaL_checkinteger(L, 1));
    auto current_time = static_cast<float>(luaL_checknumber(L, 2));
    auto delta = static_cast<float>(luaL_checknumber(L, 3));

    auto result = RhythmGameUtilities::IsOnTheBeat(bpm, current_time, delta);

    lua_pushboolean(L, static_cast<int>(result));

    return 1;
}

static auto lua_round_up_to_the_nearest_multiplier(lua_State *L) -> int
{
    auto value = static_cast<int>(luaL_checkinteger(L, 1));
    auto multiplier = static_cast<int>(luaL_checkinteger(L, 2));

    int result =
        RhythmGameUtilities::RoundUpToTheNearestMultiplier(value, multiplier);

    lua_pushinteger(L, result);

    return 1;
}

static const luaL_Reg rhythmgameutilities_functions[] = {
    {"inverse_lerp", lua_inverse_lerp},
    {"inverse_lerp_unclamped", lua_inverse_lerp_unclamped},
    {"lerp", lua_lerp},

    {"read_resolution_from_chart_data", lua_read_resolution_from_chart_data},
    {"read_tempo_changes_from_chart_data",
     lua_read_tempo_changes_from_chart_data},
    {"read_time_signature_changes_from_chart_data",
     lua_read_time_signature_changes_from_chart_data},
    {"read_notes_from_chart_data", lua_read_notes_from_chart_data},

    {"convert_seconds_to_ticks", lua_convert_seconds_to_ticks},
    {"calculate_beat_bars", lua_calculate_beat_bars},
    {"find_notes_near_given_tick", lua_find_notes_near_given_tick},
    {"calculate_accuracy_ratio", lua_calculate_accuracy_ratio},
    {"calculate_accuracy", lua_calculate_accuracy},
    {"calculate_timing", lua_calculate_timing},
    {"convert_tick_to_position", lua_convert_tick_to_position},
    {"is_on_the_beat", lua_is_on_the_beat},
    {"round_up_to_the_nearest_multiplier",
     lua_round_up_to_the_nearest_multiplier},
    {nullptr, nullptr}};

extern "C" auto luaopen_rhythmgameutilities(lua_State *L) -> int
{
    register_accuracy_enum(L);
    register_difficulty_enum(L);
    register_timing_enum(L);

    lua_newtable(L);
    luaL_register(L, nullptr, rhythmgameutilities_functions);

    return 1;
}
