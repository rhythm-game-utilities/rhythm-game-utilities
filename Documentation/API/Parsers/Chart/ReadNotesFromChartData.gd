extends Node

func _ready() -> void:
	var file: FileAccess = FileAccess.open("res://song.chart", FileAccess.READ)
	var contents: String = file.get_as_text()

	var notes: Array = rhythm_game_utilities.read_notes_from_chart_data(contents, rhythm_game_utilities.Expert)

	print(notes)
