extends Node

func _ready() -> void:
	var file: FileAccess = FileAccess.open("res://song.chart", FileAccess.READ)
	var contents: String = file.get_as_text()

	var resolution: int = rhythm_game_utilities.read_resolution_from_chart_data(contents)

	print(resolution)
