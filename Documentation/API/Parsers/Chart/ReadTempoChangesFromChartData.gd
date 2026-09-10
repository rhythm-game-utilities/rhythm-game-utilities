extends Node

func _ready() -> void:
	var file: FileAccess = FileAccess.open("res://song.chart", FileAccess.READ)
	var contents: String = file.get_as_text()

	var tempo_changes: Array = rhythm_game_utilities.read_tempo_changes_from_chart_data(contents)

	print(tempo_changes)
