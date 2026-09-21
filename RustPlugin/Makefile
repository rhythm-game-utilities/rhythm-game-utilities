help:
	@fgrep -h "##" $(MAKEFILE_LIST) | sed -e 's/##//' | tail -n +2

build: ## Build Rust plugin
	./build.sh

test: build ## Test Rust plugin
	DYLD_LIBRARY_PATH="./libs" RUSTFLAGS="-L native=./libs" cargo test

install-dependencies: ## Install Dependencies
	cargo install bindgen-cli
