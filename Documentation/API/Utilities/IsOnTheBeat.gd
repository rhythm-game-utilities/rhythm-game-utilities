extends Node

func _ready() -> void:
	var bpm: int = 120
	var current_time: int = 10
	var delta: float = 0.05

	var is_on_the_beat: bool = rhythm_game_utilities.is_on_the_beat(bpm, current_time, delta)

	if is_on_the_beat: # "Is on the beat!"
		print("Is on the beat!")
	else:
		print("Is not on the beat!")
