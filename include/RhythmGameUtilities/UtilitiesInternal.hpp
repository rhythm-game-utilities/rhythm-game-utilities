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

#include "Utilities.hpp"

#ifdef _WIN32
#define PACKAGE_API __declspec(dllexport)
#else
#define PACKAGE_API
#endif

namespace RhythmGameUtilities
{

extern "C"
{
    PACKAGE_API auto ConvertSecondsToTicksInternal(float seconds,
                                                   int resolution,
                                                   Tempo *tempoChanges,
                                                   int tempoChangesSize) -> int
    {
        std::vector<Tempo> tempoChangesVector;

        for (auto i = 0; i < tempoChangesSize; i += 1)
        {
            tempoChangesVector.push_back(tempoChanges[i]);
        }

        return ConvertSecondsToTicks(seconds, resolution, tempoChangesVector);
    }

    PACKAGE_API auto CalculateBeatBarsInternal(Tempo *tempoChanges,
                                               int tempoChangesSize,
                                               int resolution,
                                               bool includeHalfNotes,
                                               int *outSize) -> BeatBar *
    {
        std::vector<Tempo> tempoChangesVector;

        for (auto i = 0; i < tempoChangesSize; i += 1)
        {
            tempoChangesVector.push_back(tempoChanges[i]);
        }

        auto internalBeatBars =
            CalculateBeatBars(tempoChangesVector, resolution, includeHalfNotes);

        *outSize = internalBeatBars.size();

        auto *beatBars =
            (BeatBar *)std::malloc(internalBeatBars.size() * sizeof(BeatBar));

        for (auto i = 0; i < internalBeatBars.size(); i += 1)
        {
            beatBars[i] = internalBeatBars[i];
        }

        return beatBars;
    }

    PACKAGE_API auto FindNotesNearGivenTickInternal(Note *notes, int noteSize,
                                                    int tick, int delta,
                                                    int *outSize) -> Note *
    {
        std::vector<Note> notesVector;

        for (auto i = 0; i < noteSize; i += 1)
        {
            notesVector.push_back(notes[i]);
        }

        auto internalFoundNotes =
            FindNotesNearGivenTick(notesVector, tick, delta);

        *outSize = internalFoundNotes.size();

        auto *foundNotes =
            (Note *)std::malloc(internalFoundNotes.size() * sizeof(Note));

        for (auto i = 0; i < internalFoundNotes.size(); i += 1)
        {
            foundNotes[i] = internalFoundNotes[i];
        }

        return foundNotes;
    }
}

} // namespace RhythmGameUtilities
