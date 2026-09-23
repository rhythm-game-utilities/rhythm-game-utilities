help:
	@fgrep -h "##" $(MAKEFILE_LIST) | sed -e 's/##//' | tail -n +2

submodules: ## Setup Submodules
	git submodule init
	git submodule update

build-debug: submodules ## Build debug Godot plugin
	scons platform=macos arch=universal target=template_debug
	scons platform=windows arch=x86_32 target=template_debug
	scons platform=windows arch=x86_64 target=template_debug
	scons platform=web arch=wasm32 target=template_debug threads=yes
	scons platform=web arch=wasm32 target=template_debug threads=no
	scons platform=android arch=arm64 target=template_debug
	scons platform=android arch=x86_64 target=template_debug
	scons platform=ios arch=arm64 target=template_debug

build-release: submodules ## Build release Godot plugin
	scons platform=macos arch=universal target=template_release
	scons platform=windows arch=x86_32 target=template_release
	scons platform=windows arch=x86_64 target=template_release
	scons platform=web arch=wasm32 target=template_release threads=yes
	scons platform=web arch=wasm32 target=template_release threads=no
	scons platform=android arch=arm64 target=template_release
	scons platform=android arch=x86_64 target=template_release
	scons platform=ios arch=arm64 target=template_release

install-dependencies: ## Install Dependencies
	brew install scons
	brew install mingw-w64
