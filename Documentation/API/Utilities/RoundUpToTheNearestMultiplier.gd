extends Node

func _ready() -> void:
	var value: int = rhythm_game_utilities.round_up_to_the_nearest_multiplier(12, 10)

	print(value) # 20
