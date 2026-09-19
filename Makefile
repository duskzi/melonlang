
build:
	cc src/melon.c -o out/melon

run: build
	./out/melon $(ARGS)
