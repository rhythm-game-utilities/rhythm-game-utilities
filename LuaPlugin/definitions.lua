---@meta

---@enum Difficulty
Difficulty = {
    Easy = 0,
    Medium = 1,
    Hard = 2,
    Expert = 3,
}

---@class TempoChange
---@field position integer
---@field bpm integer

---@class BeatBar
---@field position integer
---@field bpm integer

---@class TimeSignatureChange
---@field position integer
---@field numerator integer
---@field denominator integer

---@class Note
---@field id integer
---@field position integer
---@field hand_position integer
---@field length integer

---@class RhythmGameUtilities
local rhythmgameutilities = {}

---@param a number
---@param b number
---@param v number
---@return number
function rhythmgameutilities.inverse_lerp(a, b, v) end

---@param a number
---@param b number
---@param v number
---@return number
function rhythmgameutilities.inverse_lerp_unclamped(a, b, v) end

---@param a number
---@param b number
---@param t number
---@return number
function rhythmgameutilities.lerp(a, b, t) end

---@param contents string
---@return integer
function rhythmgameutilities.read_resolution_from_chart_data(contents) end

---@param contents string
---@return TempoChange[]
function rhythmgameutilities.read_tempo_changes_from_chart_data(contents) end

---@param contents string
---@return TimeSignatureChange[]
function rhythmgameutilities.read_time_signature_changes_from_chart_data(contents) end

---@param contents string
---@param difficulty Difficulty|integer
---@return Note[]
function rhythmgameutilities.read_notes_from_chart_data(contents, difficulty) end

---@param data string
---@return integer
function rhythmgameutilities.read_resolution_from_midi_data(data) end

---@param data string
---@return TempoChange[]
function rhythmgameutilities.read_tempo_changes_from_midi_data(data) end

---@param data string
---@return TimeSignatureChange[]
function rhythmgameutilities.read_time_signature_changes_from_midi_data(data) end

---@param data string
---@return Note[]
function rhythmgameutilities.read_notes_from_midi_data(data) end

---@param seconds number
---@param resolution integer
---@param tempo_changes TempoChange[]
---@return number
function rhythmgameutilities.convert_seconds_to_ticks(seconds, resolution, tempo_changes) end

---@param tempo_changes TempoChange[]
---@param resolution integer
---@param include_half_notes boolean
---@return BeatBar[]
function rhythmgameutilities.calculate_beat_bars(tempo_changes, resolution, include_half_notes) end

---@param notes Note[]
---@param tick integer
---@param delta integer
---@return Note[]
function rhythmgameutilities.find_notes_near_given_tick(notes, tick, delta) end

---@param position integer
---@param current_position integer
---@param delta integer
---@return number
function rhythmgameutilities.calculate_accuracy_ratio(position, current_position, delta) end

---@param position integer
---@param current_position integer
---@param delta integer
---@return string
function rhythmgameutilities.calculate_accuracy(position, current_position, delta) end

---@param position integer
---@param current_position integer
---@param delta integer
---@return string
function rhythmgameutilities.calculate_timing(position, current_position, delta) end

---@param tick integer
---@param resolution integer
---@return number
function rhythmgameutilities.convert_tick_to_position(tick, resolution) end

---@param bpm integer
---@param current_time number
---@param delta number
---@return boolean
function rhythmgameutilities.is_on_the_beat(bpm, current_time, delta) end

---@param value integer
---@param multiplier integer
---@return integer
function rhythmgameutilities.round_up_to_the_nearest_multiplier(value, multiplier) end

return rhythmgameutilities
