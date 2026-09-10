extends Node

func _ready() -> void:
	var tick: int = 1056
	var resolution: int = 192

	var position: float = rhythm_game_utilities.convert_tick_to_position(tick, resolution)

	print(position) # 5.5
