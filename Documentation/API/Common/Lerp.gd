extends Node

func _ready() -> void:
	var value: float = rhythm_game_utilities.lerp(0, 10, 0.5)

	print(value) # 5
