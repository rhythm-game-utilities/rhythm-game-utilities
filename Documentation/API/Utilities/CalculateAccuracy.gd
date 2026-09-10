extends Node

func _ready() -> void:
	var seconds: int = 2
	var resolution: int = 192
	var position_delta: int = 50

	var tempo_changes: Array = [
		{"position": 0, "bpm": 120000}
	]

	var current_position: int = rhythm_game_utilities.convert_seconds_to_ticks(seconds, resolution, tempo_changes)

	var accuracy: int = rhythm_game_utilities.calculate_accuracy(750, current_position, position_delta)

	match accuracy:
		rhythm_game_utilities.Poor:
			print("Poor")
		rhythm_game_utilities.Fair:
			print("Fair")
		rhythm_game_utilities.Good:
			print("Good")
		rhythm_game_utilities.Great:
			print("Great")
		rhythm_game_utilities.Perfect:
			print("Perfect")
