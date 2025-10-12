#include "RhythmGameUtilities/Common.hpp"
#include "RhythmGameUtilities/Enums/Accuracy.hpp"
#include "RhythmGameUtilities/Enums/Difficulty.hpp"
#include "RhythmGameUtilities/Enums/Timing.hpp"
#include "RhythmGameUtilities/Parsers/Chart.hpp"
#include "RhythmGameUtilities/Utilities.hpp"

#include <lua/lua.hpp>

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
    float a = luaL_checknumber(L, 1);
    float b = luaL_checknumber(L, 2);
    float v = luaL_checknumber(L, 3);

    float result = RhythmGameUtilities::InverseLerp(a, b, v);

    lua_pushnumber(L, result);

    return 1;
}

static auto lua_inverse_lerp_unclamped(lua_State *L) -> int
{
    float a = luaL_checknumber(L, 1);
    float b = luaL_checknumber(L, 2);
    float v = luaL_checknumber(L, 3);

    float result = RhythmGameUtilities::InverseLerpUnclamped(a, b, v);

    lua_pushnumber(L, result);

    return 1;
}

static auto lua_lerp(lua_State *L) -> int
{
    float a = luaL_checknumber(L, 1);
    float b = luaL_checknumber(L, 2);
    float t = luaL_checknumber(L, 3);

    float result = RhythmGameUtilities::Lerp(a, b, t);

    lua_pushnumber(L, result);

    return 1;
}

// Chart

static auto lua_read_resolution_from_chart_data(lua_State *L) -> int
{
    std::string contents = luaL_checkstring(L, 1);

    float result =
        RhythmGameUtilities::ReadResolutionFromChartData(contents.c_str());

    lua_pushnumber(L, result);

    return 1;
}

static auto lua_read_tempo_changes_from_chart_data(lua_State *L) -> int
{
    std::string contents = luaL_checkstring(L, 1);

    auto result =
        RhythmGameUtilities::ReadTempoChangesFromChartData(contents.c_str());

    lua_createtable(L, static_cast<int>(result.size()), 0);

    for (auto i = 0; i < result.size(); i += 1)
    {
        lua_createtable(L, 0, 2);

        lua_pushnumber(L, result[i].Position);
        lua_setfield(L, -2, "position");

        lua_pushnumber(L, result[i].BPM);
        lua_setfield(L, -2, "bpm");

        lua_rawseti(L, -2, static_cast<lua_Integer>(i + 1));
    }

    return 1;
}

static auto lua_read_time_signature_changes_from_chart_data(lua_State *L) -> int
{
    std::string contents = luaL_checkstring(L, 1);

    auto result = RhythmGameUtilities::ReadTimeSignatureChangesFromChartData(
        contents.c_str());

    lua_createtable(L, static_cast<int>(result.size()), 0);

    for (auto i = 0; i < result.size(); i += 1)
    {
        lua_createtable(L, 0, 3);

        lua_pushnumber(L, result[i].Position);
        lua_setfield(L, -2, "position");

        lua_pushnumber(L, result[i].Numerator);
        lua_setfield(L, -2, "numerator");

        lua_pushnumber(L, result[i].Denominator);
        lua_setfield(L, -2, "denominator");

        lua_rawseti(L, -2, static_cast<lua_Integer>(i + 1));
    }

    return 1;
}

static auto lua_read_notes_from_chart_data(lua_State *L) -> int
{
    std::string contents = luaL_checkstring(L, 1);

    auto diff_int = static_cast<int>(luaL_checkinteger(L, 2));
    auto difficulty = static_cast<RhythmGameUtilities::Difficulty>(diff_int);

    auto result = RhythmGameUtilities::ReadNotesFromChartData(contents.c_str(),
                                                              difficulty);

    lua_createtable(L, static_cast<int>(result.size()), 0);

    for (auto i = 0; i < result.size(); i += 1)
    {
        lua_createtable(L, 0, 4);

        lua_pushnumber(L, result[i].ID);
        lua_setfield(L, -2, "id");

        lua_pushnumber(L, result[i].Position);
        lua_setfield(L, -2, "position");

        lua_pushnumber(L, result[i].HandPosition);
        lua_setfield(L, -2, "hand_position");

        lua_pushnumber(L, result[i].Length);
        lua_setfield(L, -2, "length");

        lua_rawseti(L, -2, static_cast<lua_Integer>(i + 1));
    }

    return 1;
}

// Utilities

static auto lua_calculate_accuracy_ratio(lua_State *L) -> int
{
    int position = luaL_checknumber(L, 1);
    int current_position = luaL_checknumber(L, 2);
    int delta = luaL_checknumber(L, 3);

    float result = RhythmGameUtilities::CalculateAccuracyRatio(
        position, current_position, delta);

    lua_pushnumber(L, result);

    return 1;
}

static auto lua_convert_tick_to_position(lua_State *L) -> int
{
    int tick = luaL_checknumber(L, 1);
    int resolution = luaL_checknumber(L, 2);

    float result = RhythmGameUtilities::ConvertTickToPosition(tick, resolution);

    lua_pushnumber(L, result);

    return 1;
}

static auto lua_is_on_the_beat(lua_State *L) -> int
{
    int bpm = luaL_checknumber(L, 1);
    float current_time = luaL_checknumber(L, 2);
    float delta = luaL_checknumber(L, 3);

    bool result = RhythmGameUtilities::IsOnTheBeat(bpm, current_time, delta);

    lua_pushboolean(L, result);

    return 1;
}

static auto lua_round_up_to_the_nearest_multiplier(lua_State *L) -> int
{
    int value = luaL_checknumber(L, 1);
    int multiplier = luaL_checknumber(L, 2);

    int result =
        RhythmGameUtilities::RoundUpToTheNearestMultiplier(value, multiplier);

    lua_pushnumber(L, result);

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
    {"calculate_accuracy_ratio", lua_calculate_accuracy_ratio},
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
    luaL_newlib(L, rhythmgameutilities_functions);
    return 1;
}
