extends Node

func _ready() -> void:
	var value: float = rhythm_game_utilities.inverse_lerp(0, 10, 5)

	print(value) # 0.5
