extends Node

func _ready() -> void:
	var delta: int = 50

	var notes: Array = [
		{"position": 768}, {"position": 960}, {"position": 1152},
		{"position": 1536}, {"position": 1728}, {"position": 1920},
		{"position": 2304}, {"position": 2496}, {"position": 2688},
		{"position": 3072}, {"position": 3264}
	]

	var found_notes: Array = rhythm_game_utilities.find_notes_near_given_tick(notes, 750, delta);

	print(found_notes[0]["position"]) # 768
