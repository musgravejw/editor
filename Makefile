editor:
	@$(CC) editor.c -o ./bin/editor -Wall -Wextra -pedantic -std=c99

clean:
	rm -rf ./bin/*

install:
	cp ./bin/editor /usr/local/bin/editor