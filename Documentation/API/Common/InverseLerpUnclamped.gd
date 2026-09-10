extends Node

func _ready() -> void:
	var value: float = rhythm_game_utilities.inverse_lerp_unclamped(0, 10, 11)

	print(value) # 1.1
