extends Node

func _ready() -> void:
	var seconds: int = 5
	var resolution: int = 192

	var tempo_changes: Array = [
		{"position": 0, "bpm": 88000},
		{"position": 3840, "bpm": 112000},
		{"position": 9984, "bpm": 89600},
		{"position": 22272, "bpm": 112000},
		{"position": 33792, "bpm": 111500},
		{"position": 34560, "bpm": 112000},
		{"position": 42240, "bpm": 111980}
	]

	var current_position: int = rhythm_game_utilities.convert_seconds_to_ticks(seconds, resolution, tempo_changes)

	print(current_position) # 1408
