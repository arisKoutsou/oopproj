# makefile

SOURCE_DIR = ./src
SOURCE_FILES = $(wildcard $(SOURCE_DIR)/*.cpp)

RolePlayingGame: $(SOURCE_FILES)
	g++ $(SOURCE_FILES) -o RolePlayingGame



