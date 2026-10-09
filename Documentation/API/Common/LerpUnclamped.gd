extends Node

func _ready() -> void:
	var value: float = rhythm_game_utilities.lerp_unclamped(0, 10, 1.1)

	print(value) # 11
