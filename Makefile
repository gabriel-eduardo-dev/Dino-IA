.PHONY: all build run

all: build run

build:
	cmake -S . -G"Unix Makefiles" -B build
	make -C build

run: bin/dino-ia
	./bin/dino-ia
