// Rhythm Game Utilities -
// https://github.com/rhythm-game-utilities/rhythm-game-utilities
//
// ░█▀▄░█░█░█░█░▀█▀░█░█░█▄█░░░█▀▀░█▀█░█▄█░█▀▀░░░█░█░▀█▀░▀█▀░█░░░▀█▀░▀█▀░▀█▀░█▀▀░█▀▀
// ░█▀▄░█▀█░░█░░░█░░█▀█░█░█░░░█░█░█▀█░█░█░█▀▀░░░█░█░░█░░░█░░█░░░░█░░░█░░░█░░█▀▀░▀▀█
// ░▀░▀░▀░▀░░▀░░░▀░░▀░▀░▀░▀░░░▀▀▀░▀░▀░▀░▀░▀▀▀░░░▀▀▀░░▀░░▀▀▀░▀▀▀░▀▀▀░░▀░░▀▀▀░▀▀▀░▀▀▀
//
// Copyright (c) Scott Doxey. All Rights Reserved. Licensed under the MIT
// License. See LICENSE in the project root for license information.

#pragma once

#include <algorithm>
#include <map>
#include <regex>
#include <string>
#include <vector>

#include "../Enums/Difficulty.hpp"
#include "../Enums/NamedSection.hpp"
#include "../Enums/TypeCode.hpp"

#include "../Structs/Note.hpp"
#include "../Structs/Tempo.hpp"
#include "../Structs/TimeSignature.hpp"

#include "../Common.hpp"

#ifdef _WIN32
#define PACKAGE_API __declspec(dllexport)
#else
#define PACKAGE_API
#endif

namespace RhythmGameUtilities
{

inline std::map<
    size_t,
    std::map<std::string,
             std::vector<std::pair<std::string, std::vector<std::string>>>>>
    parsedChartCache;

inline std::regex CHART_SECTION_PATTERN(R"(\[([a-z]+)\]\s*\{([^\}]+)\})",
                                        std::regex_constants::icase);

inline std::regex CHART_SECTION_LINE_PATTERN(R"(([^=]+)\s*=([^\r\n]+))");

inline std::regex JSON_VALUE_PATTERN(R"(("[^"]+"|\S+))");

inline auto ParseSectionsFromChart(const std::string &contents)
    -> std::map<std::string,
                std::vector<std::pair<std::string, std::vector<std::string>>>>
{
    auto cacheKey = std::hash<std::string>{}(contents);

    auto match = parsedChartCache.find(cacheKey);

    if (match != parsedChartCache.end())
    {
        return match->second;
    }

    auto matches = FindAllMatches(contents, CHART_SECTION_PATTERN);

    std::map<std::string,
             std::vector<std::pair<std::string, std::vector<std::string>>>>
        sections;

    for (std::size_t i = 0; i < matches.size(); i += 1)
    {
        auto parts = FindMatchGroups(matches[i], CHART_SECTION_PATTERN);

        if (parts.size() < 3)
        {
            continue;
        }

        auto lines = FindAllMatches(parts[2], CHART_SECTION_LINE_PATTERN);

        std::vector<std::pair<std::string, std::vector<std::string>>> items;

        for (std::size_t j = 0; j < lines.size(); j += 1)
        {
            auto parts = Split(lines[j], '=');

            auto key = Trim(parts[0]);
            auto value = Trim(parts[1]);

            auto values = FindAllMatches(value, JSON_VALUE_PATTERN);

            for (std::size_t k = 0; k < values.size(); k += 1)
            {
                values[k] =
                    std::regex_replace(values[k], std::regex("^\"|\"$"), "");
            }

            items.emplace_back(key, values);
        }

        sections.insert({parts[1].c_str(), items});
    }

    parsedChartCache.insert_or_assign(cacheKey, sections);

    return sections;
}

extern "C"
{
    PACKAGE_API auto ReadResolutionFromChartData(const char *contents)
        -> uint16_t
    {
        auto sections = ParseSectionsFromChart(contents);

        auto sectionIter = sections.find(ToString(NamedSection::Song));

        if (sectionIter == sections.end())
        {
            return 0;
        }

        const auto &section = sectionIter->second;

        auto data = std::map<std::string, std::string>();

        for (const auto &line : section)
        {
            std::string key = line.first;
            std::transform(key.begin(), key.end(), key.begin(),
                           [](unsigned char c) -> int
                           { return std::tolower(c); });

            if (key == "resolution")
            {
                return std::stoi(line.second.front());
            }
        }

        return 0;
    }
}

inline auto ReadTempoChangesFromChartData(const std::string &contents)
    -> std::vector<Tempo>
{
    auto tempoChanges = std::vector<Tempo>();

    auto sections = ParseSectionsFromChart(contents);

    auto sectionIter = sections.find(ToString(NamedSection::SyncTrack));

    if (sectionIter == sections.end())
    {
        return tempoChanges;
    }

    const auto &section = sectionIter->second;

    for (const auto &line : section)
    {
        if (line.second.size() >= 1 &&
            line.second.front() == ToString(TypeCode::BPM_Marker))
        {
            tempoChanges.emplace_back(std::stoi(line.first),
                                      std::stoi(line.second.at(1)));
        }
    }

    std::sort(tempoChanges.begin(), tempoChanges.end(),
              [](const Tempo &a, const Tempo &b) -> bool
              { return a.Position < b.Position; });

    return tempoChanges;
}

inline auto ReadTimeSignatureChangesFromChartData(const std::string &contents)
    -> std::vector<TimeSignature>
{
    auto timeSignatureChanges = std::vector<TimeSignature>();

    auto sections = ParseSectionsFromChart(contents);

    auto sectionIter = sections.find(ToString(NamedSection::SyncTrack));

    if (sectionIter == sections.end())
    {
        return timeSignatureChanges;
    }

    const auto &section = sectionIter->second;

    for (const auto &line : section)
    {
        if (line.second.size() >= 2 &&
            line.second.front() == ToString(TypeCode::TimeSignatureMarker))
        {
            timeSignatureChanges.emplace_back(
                std::stoi(line.first), std::stoi(line.second.at(1)),
                line.second.size() > 2 ? std::stoi(line.second.at(2)) : 2);
        }
    }

    std::sort(timeSignatureChanges.begin(), timeSignatureChanges.end(),
              [](const TimeSignature &a, const TimeSignature &b) -> bool
              { return a.Position < b.Position; });

    return timeSignatureChanges;
}

inline auto ReadNotesFromChartData(const std::string &contents,
                                   Difficulty difficulty) -> std::vector<Note>
{
    auto sections = ParseSectionsFromChart(contents);

    auto section = sections.at(ToString(difficulty) + "Single");

    auto notes = std::vector<Note>();

    int id = 0;

    for (const auto &line : section)
    {
        if (line.second.size() >= 2 &&
            line.second.front() == ToString(TypeCode::NoteMarker))
        {
            notes.emplace_back(++id, std::stoi(line.first),
                               std::stoi(line.second.at(1)),
                               std::stoi(line.second.at(2)));
        }
    }

    std::sort(notes.begin(), notes.end(),
              [](const Note &a, const Note &b) -> bool
              {
                  if (a.Position != b.Position)
                  {
                      return a.Position < b.Position;
                  }

                  return a.HandPosition < b.HandPosition;
              });

    return notes;
}

inline auto ReadLyricsFromChartData(const std::string &contents)
    -> std::map<int, std::string>
{
    auto sections = ParseSectionsFromChart(contents);

    auto section = sections.at(ToString(NamedSection::Events));

    auto lyrics = std::map<int, std::string>();

    for (const auto &line : section)
    {
        if (line.second.back().rfind("lyric", 0) == 0)
        {
            lyrics.insert({std::stoi(line.first), line.second.at(1)});
        }
    }

    return lyrics;
}

} // namespace RhythmGameUtilities
