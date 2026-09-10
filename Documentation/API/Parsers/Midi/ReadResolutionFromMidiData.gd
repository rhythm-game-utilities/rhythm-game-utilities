extends Node

func _ready() -> void:
	var file: FileAccess = FileAccess.open("res://song.mid", FileAccess.READ)
	var bytes: PackedByteArray = file.get_buffer(file.get_length())

	var resolution: int = rhythm_game_utilities.read_resolution_from_midi_data(bytes)

	print(resolution)
