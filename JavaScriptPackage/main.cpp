#include <emscripten/bind.h>

#include "./RhythmGameUtilities/Common.hpp"
#include "./RhythmGameUtilities/Utilities.hpp"

#include "./RhythmGameUtilities/Parsers/Chart.hpp"

using namespace RhythmGameUtilities;

inline auto DifficultyFromString(const std::string &difficulty) -> Difficulty
{
    if (difficulty == "Easy")
    {
        return Difficulty::Easy;
    }

    if (difficulty == "Medium")
    {
        return Difficulty::Medium;
    }

    if (difficulty == "Hard")
    {
        return Difficulty::Hard;
    }

    if (difficulty == "Expert")
    {
        return Difficulty::Expert;
    }

    throw std::invalid_argument("Unknown Difficulty: " + difficulty);
}

EMSCRIPTEN_BINDINGS(my_module)
{
    // Common

    emscripten::function("Lerp", &Lerp);
    emscripten::function("InverseLerp", &InverseLerp);
    emscripten::function("InverseLerpUnclamped", &InverseLerpUnclamped);

    // Utilities

    emscripten::function("ConvertTickToPosition", &ConvertTickToPosition);
    emscripten::function("IsOnTheBeat", &IsOnTheBeat);
    emscripten::function("RoundUpToTheNearestMultiplier",
                         &RoundUpToTheNearestMultiplier);
    emscripten::function("CalculateAccuracyRatio", &CalculateAccuracyRatio);

    emscripten::function(
        "CalculateAccuracy",
        emscripten::optional_override(
            [](int position, int currentPosition, int delta = 50) -> std::string
            {
                auto accuracy =
                    CalculateAccuracy(position, currentPosition, delta);

                return ToString(accuracy);
            }));

    emscripten::function(
        "CalculateTiming",
        emscripten::optional_override(
            [](int position, int currentPosition, int delta = 50) -> std::string
            {
                auto accuracy =
                    CalculateTiming(position, currentPosition, delta);

                return ToString(accuracy);
            }));

    emscripten::function("ConvertSecondsToTicks",
                         emscripten::optional_override(
                             [](float seconds, int resolution,
                                const emscripten::val &tempoChanges) -> int
                             {
                                 const auto length =
                                     tempoChanges["length"].as<unsigned>();

                                 std::vector<Tempo> internalTempoChanges;
                                 internalTempoChanges.reserve(length);

                                 for (auto i = 0; i < length; i += 1)
                                 {
                                     internalTempoChanges.emplace_back(
                                         tempoChanges[i]["position"].as<int>(),
                                         tempoChanges[i]["bpm"].as<int>());
                                 }

                                 auto ticks = ConvertSecondsToTicks(
                                     seconds, resolution, internalTempoChanges);

                                 return ticks;
                             }));

    emscripten::function(
        "CalculateBeatBars",
        emscripten::optional_override(
            [](const emscripten::val &tempoChanges, int resolution,
               bool includeHalfNotes) -> emscripten::val
            {
                const auto length = tempoChanges["length"].as<unsigned>();

                std::vector<Tempo> internalTempoChanges;
                internalTempoChanges.reserve(length);

                for (auto i = 0; i < length; i += 1)
                {
                    internalTempoChanges.emplace_back(
                        tempoChanges[i]["position"].as<int>(),
                        tempoChanges[i]["bpm"].as<int>());
                }

                auto beatBars = CalculateBeatBars(internalTempoChanges,
                                                  resolution, includeHalfNotes);

                auto result = emscripten::val::array();

                for (const auto &beatBar : beatBars)
                {
                    auto obj = emscripten::val::object();
                    obj.set("position", beatBar.Position);
                    obj.set("bpm", beatBar.BPM);
                    result.call<void>("push", obj);
                }

                return result;
            }));

    emscripten::function("FindNotesNearGivenTick",
                         emscripten::optional_override(
                             [](const emscripten::val &notes, int tick,
                                int delta) -> emscripten::val
                             {
                                 const auto length =
                                     notes["length"].as<unsigned>();

                                 std::vector<Note> internalNotes;
                                 internalNotes.reserve(length);

                                 for (auto i = 0; i < length; i += 1)
                                 {
                                     internalNotes.emplace_back(
                                         notes[i]["id"].as<int>(),
                                         notes[i]["position"].as<int>(),
                                         notes[i]["handPosition"].as<int>(),
                                         notes[i]["length"].as<int>());
                                 }

                                 auto foundNotes = FindNotesNearGivenTick(
                                     internalNotes, tick, delta);

                                 auto result = emscripten::val::array();

                                 for (const auto &note : foundNotes)
                                 {
                                     auto obj = emscripten::val::object();
                                     obj.set("id", note.ID);
                                     obj.set("position", note.Position);
                                     obj.set("handPosition", note.HandPosition);
                                     obj.set("length", note.Length);
                                     result.call<void>("push", obj);
                                 }

                                 return result;
                             }));

    // Parsers/Chart

    emscripten::function(
        "ReadResolutionFromChartData",
        emscripten::optional_override(
            [](const std::string &contents) -> uint16_t
            { return ReadResolutionFromChartData(contents.c_str()); }));

    emscripten::function("ReadTempoChangesFromChartData",
                         emscripten::optional_override(
                             [](const std::string &contents) -> emscripten::val
                             {
                                 auto tempoChanges =
                                     ReadTempoChangesFromChartData(contents);

                                 auto result = emscripten::val::array();

                                 for (const auto &tempoChange : tempoChanges)
                                 {
                                     auto obj = emscripten::val::object();
                                     obj.set("position", tempoChange.Position);
                                     obj.set("bpm", tempoChange.BPM);
                                     result.call<void>("push", obj);
                                 }

                                 return result;
                             }));

    emscripten::function(
        "ReadTimeSignatureChangesFromChartData",
        emscripten::optional_override(
            [](const std::string &contents) -> emscripten::val
            {
                auto timeSignatureChanges =
                    ReadTimeSignatureChangesFromChartData(contents);

                auto result = emscripten::val::array();

                for (const auto &timeSignatureChange : timeSignatureChanges)
                {
                    auto obj = emscripten::val::object();
                    obj.set("position", timeSignatureChange.Position);
                    obj.set("numerator", timeSignatureChange.Numerator);
                    obj.set("denominator", timeSignatureChange.Denominator);
                    result.call<void>("push", obj);
                }

                return result;
            }));

    emscripten::function(
        "ReadNotesFromChartData",
        emscripten::optional_override(
            [](const std::string &contents,
               const std::string &difficulty) -> emscripten::val
            {
                auto notes = ReadNotesFromChartData(
                    contents, DifficultyFromString(difficulty));

                auto result = emscripten::val::array();

                for (const auto &note : notes)
                {
                    auto obj = emscripten::val::object();
                    obj.set("id", note.ID);
                    obj.set("position", note.Position);
                    obj.set("handPosition", note.HandPosition);
                    obj.set("length", note.Length);
                    result.call<void>("push", obj);
                }

                return result;
            }));
}
