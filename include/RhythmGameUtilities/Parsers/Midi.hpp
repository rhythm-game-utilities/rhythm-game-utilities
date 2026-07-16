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
#include <cstdint>
#include <cstring>
#include <optional>
#include <string>
#include <vector>

#include "../Structs/Note.hpp"
#include "../Structs/Tempo.hpp"
#include "../Structs/TimeSignature.hpp"

namespace RhythmGameUtilities
{

inline auto ByteSwap(uint16_t value) -> uint16_t
{
    return (value >> 8) | (value << 8);
}

inline auto ByteSwap(uint32_t value) -> uint32_t
{
    return ((value >> 24) & 0xFF) | ((value >> 8) & 0xFF00) |
           ((value << 8) & 0xFF0000) | ((value << 24) & 0xFF000000);
}

struct ByteStream
{
    const uint8_t *data;
    size_t size;
    size_t pos = 0;

    [[nodiscard]] auto good() const -> bool { return pos < size; }

    auto seek(int offset) -> void { pos += static_cast<size_t>(offset); }

    auto read(void *dest, size_t len) -> bool
    {
        if (pos + len > size)
        {
            return false;
        }

        std::memcpy(dest, data + pos, len);
        pos += len;

        return true;
    }
};

template <typename T> inline auto ReadChunk(ByteStream &stream) -> T
{
    T chunk{};
    stream.read(&chunk, sizeof(T));
    return chunk;
}

inline auto ReadString(ByteStream &stream, size_t length) -> std::string
{
    auto chunk = std::string(length, '\0');
    return stream.read(chunk.data(), length) ? chunk : "";
}

inline auto ReadVarLen(ByteStream &stream) -> uint32_t
{
    uint32_t value = 0;
    uint8_t byte = 0;
    do
    {
        if (!stream.good())
        {
            return value;
        }
        byte = ReadChunk<uint8_t>(stream);
        value = (value << 7) | (byte & 0x7F);
    } while ((byte & 0x80) > 0);
    return value;
}

constexpr auto META_EVENT = 0xFF;
constexpr auto END_OF_TRACK = 0x2F;
constexpr auto SYSTEM_COMMAND = 0xF0;
constexpr auto TEMPO_CHANGE = 0x51;
constexpr auto TIME_SIGNATURE_CHANGE = 0x58;
constexpr auto NOTE_ON_COMMAND = 0x90;
constexpr auto PROGRAM_CHANGE_COMMAND = 0xC0;
constexpr auto CHANNEL_PRESSURE_COMMAND = 0xD0;

using MidiEventType = enum : uint8_t { Meta, NoteOn };

struct MidiHeader
{
    uint32_t length;
    uint16_t format;
    uint16_t trackCount;
    uint16_t resolution;
};

inline auto ReadMidiHeader(ByteStream &stream) -> std::optional<MidiHeader>
{
    if (ReadString(stream, 4) != "MThd")
    {
        return std::nullopt;
    }

    return MidiHeader{ByteSwap(ReadChunk<uint32_t>(stream)),
                      ByteSwap(ReadChunk<uint16_t>(stream)),
                      ByteSwap(ReadChunk<uint16_t>(stream)),
                      ByteSwap(ReadChunk<uint16_t>(stream))};
}

inline auto CreateMidiStream(const std::vector<uint8_t> &data)
    -> std::pair<ByteStream, std::optional<MidiHeader>>
{
    auto stream = ByteStream{data.data(), data.size()};

    return {stream, ReadMidiHeader(stream)};
}

template <typename Callback>
inline auto ForEachMidiEvent(const std::vector<uint8_t> &data,
                             Callback &&callback) -> bool
{
    auto [stream, header] = CreateMidiStream(data);

    if (!header)
    {
        return false;
    }

    for (auto t = 0; t < header->trackCount; t += 1)
    {
        if (ReadString(stream, 4) != "MTrk")
        {
            break;
        }

        stream.seek(4);

        uint32_t tick = 0;

        while (stream.good())
        {
            tick += ReadVarLen(stream);

            auto status = ReadChunk<uint8_t>(stream);

            if (status == META_EVENT)
            {
                auto type = ReadChunk<uint8_t>(stream);

                auto length = ReadVarLen(stream);

                if (type == END_OF_TRACK)
                {
                    break;
                }

                auto next = stream.pos + length;

                callback(MidiEventType::Meta, tick, type, length, stream);

                stream.pos = next;
            }
            else if ((status & SYSTEM_COMMAND) == NOTE_ON_COMMAND)
            {
                callback(MidiEventType::NoteOn, tick, uint8_t{0}, uint32_t{0},
                         stream);
            }
            else if ((status & SYSTEM_COMMAND) == PROGRAM_CHANGE_COMMAND ||
                     (status & SYSTEM_COMMAND) == CHANNEL_PRESSURE_COMMAND)
            {
                stream.seek(1);
            }
            else
            {
                stream.seek(2);
            }
        }
    }

    return true;
}

inline auto ReadResolutionFromMidiData(const std::vector<uint8_t> &data)
    -> uint16_t
{
    auto [stream, header] = CreateMidiStream(data);

    return header ? header->resolution : 0;
}

inline auto ReadTempoChangesFromMidiData(const std::vector<uint8_t> &data)
    -> std::vector<Tempo>
{
    auto tempoChanges = std::vector<Tempo>{};

    ForEachMidiEvent(
        data,
        [&](MidiEventType eventType, uint32_t tick, uint8_t metaType,
            uint32_t length, ByteStream &stream) -> void
        {
            if (eventType == MidiEventType::Meta && metaType == TEMPO_CHANGE &&
                length == 3)
            {
                auto b1 = static_cast<uint32_t>(ReadChunk<uint8_t>(stream));
                auto b2 = static_cast<uint32_t>(ReadChunk<uint8_t>(stream));
                auto b3 = static_cast<uint32_t>(ReadChunk<uint8_t>(stream));

                auto microsecondsPerBeat = (b1 << 16) | (b2 << 8) | b3;

                tempoChanges.push_back(
                    {static_cast<int>(tick),
                     static_cast<int>(60000000000 / microsecondsPerBeat)});
            }
        });

    if (tempoChanges.empty())
    {
        tempoChanges.push_back({0, 120000});
    }

    std::sort(tempoChanges.begin(), tempoChanges.end(),
              [](const Tempo &a, const Tempo &b) -> bool
              { return a.Position < b.Position; });

    return tempoChanges;
}

inline auto
ReadTimeSignatureChangesFromMidiData(const std::vector<uint8_t> &data)
    -> std::vector<TimeSignature>
{
    auto timeSignatureChanges = std::vector<TimeSignature>{};

    ForEachMidiEvent(
        data,
        [&](MidiEventType eventType, uint32_t tick, uint8_t metaType,
            uint32_t length, ByteStream &stream) -> void
        {
            if (eventType == MidiEventType::Meta &&
                metaType == TIME_SIGNATURE_CHANGE && length >= 2)
            {
                auto numerator = ReadChunk<uint8_t>(stream);
                auto denominator =
                    static_cast<uint8_t>(1 << ReadChunk<uint8_t>(stream));

                timeSignatureChanges.push_back(
                    {static_cast<int>(tick), numerator, denominator});
            }
        });

    std::sort(timeSignatureChanges.begin(), timeSignatureChanges.end(),
              [](const TimeSignature &a, const TimeSignature &b) -> bool
              { return a.Position < b.Position; });

    return timeSignatureChanges;
}

inline auto ReadNotesFromMidiData(const std::vector<uint8_t> &data)
    -> std::vector<Note>
{
    auto notes = std::vector<Note>{};

    int id = 0;

    ForEachMidiEvent(data,
                     [&](MidiEventType eventType, uint32_t tick, uint8_t,
                         uint32_t, ByteStream &stream) -> void
                     {
                         if (eventType == MidiEventType::NoteOn)
                         {
                             auto noteValue = ReadChunk<uint8_t>(stream);

                             stream.seek(1);

                             notes.push_back(
                                 Note{++id, static_cast<int>(tick), noteValue});
                         }
                     });

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

} // namespace RhythmGameUtilities
