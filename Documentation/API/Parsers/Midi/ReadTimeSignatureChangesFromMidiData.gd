extends Node

func _ready() -> void:
	var file: FileAccess = FileAccess.open("res://song.mid", FileAccess.READ)
	var bytes: PackedByteArray = file.get_buffer(file.get_length())

	var time_signature_changes: Array = rhythm_game_utilities.read_time_signature_changes_from_midi_data(bytes)

	print(time_signature_changes)
