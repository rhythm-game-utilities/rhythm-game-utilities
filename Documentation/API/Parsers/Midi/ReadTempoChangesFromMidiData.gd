extends Node

func _ready() -> void:
	var file: FileAccess = FileAccess.open("res://song.mid", FileAccess.READ)
	var bytes: PackedByteArray = file.get_buffer(file.get_length())

	var tempo_changes: Array = rhythm_game_utilities.read_tempo_changes_from_midi_data(bytes)

	print(tempo_changes)
