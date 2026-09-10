extends Node

func _ready() -> void:
	var seconds: int = 2
	var resolution: int = 192
	var position_delta: int = 50

	var tempo_changes: Array = [
		{"position": 0, "bpm": 120000}
	]

	var current_position: int = rhythm_game_utilities.convert_seconds_to_ticks(seconds, resolution, tempo_changes)

	var timing: int = rhythm_game_utilities.calculate_timing(750, current_position, position_delta)

	match timing:
		rhythm_game_utilities.Miss:
			print("Miss")
		rhythm_game_utilities.Hit:
			print("Hit")
		rhythm_game_utilities.Early:
			print("Early")
		rhythm_game_utilities.Late:
			print("Late")
