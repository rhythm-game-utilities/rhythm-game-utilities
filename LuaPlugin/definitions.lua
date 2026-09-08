---@meta

---@enum Difficulty
Difficulty = {
    Easy = 0,
    Medium = 1,
    Hard = 2,
    Expert = 3,
}

---@class TempoChange
---@field position number
---@field bpm number

---@class TimeSignatureChange
---@field position number
---@field numerator number
---@field denominator number

---@class Note
---@field id number
---@field position number
---@field hand_position number
---@field length number

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
---@return number
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

---@param position number
---@param current_position number
---@param delta number
---@return number
function rhythmgameutilities.calculate_accuracy_ratio(position, current_position, delta) end

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
