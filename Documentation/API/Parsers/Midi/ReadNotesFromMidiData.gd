extends Node

func _ready() -> void:
	var file: FileAccess = FileAccess.open("res://song.mid", FileAccess.READ)
	var bytes: PackedByteArray = file.get_buffer(file.get_length())

	var notes: Array = rhythm_game_utilities.read_notes_from_midi_data(bytes)

	print(notes)
