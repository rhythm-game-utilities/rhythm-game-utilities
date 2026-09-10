extends Node

func _ready() -> void:
	var seconds: int = 2
	var resolution: int = 192
	var position_delta: int = 50

	var tempo_changes: Array = [
		{"position": 0, "bpm": 120000 }
	]

	var current_position: int = rhythm_game_utilities.convert_seconds_to_ticks(seconds, resolution, tempo_changes)

	var value: float = rhythm_game_utilities.calculate_accuracy_ratio(750, current_position, position_delta)

	print(round(value * 100) / 100.0) # 0.64
