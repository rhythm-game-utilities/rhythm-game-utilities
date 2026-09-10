extends Node

func _ready() -> void:
	var resolution: int = 192

	var tempo_changes: Array = [
		{"position": 0, "bpm": 8800},
		{"position": 3840, "bpm": 112000},
		{"position": 9984, "bpm": 89600},
		{"position": 22272, "bpm": 112000},
		{"position": 33792, "bpm": 111500},
		{"position": 34560, "bpm": 112000},
		{"position": 42240, "bpm": 111980}
	]

	var beat_bars: Array = rhythm_game_utilities.calculate_beat_bars(tempo_changes, resolution, true)

	print(beat_bars)
