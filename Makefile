# --------------------------------------------------------------------
#  Makefile Lab4.

# Define a set of rules.
# Each rule has a target, dependencies  and commands.
# target: dependencies
#	command1
#	command2
#	command3

# make objetivo

# --------------------------------------------------------------------
# --------------------------------------------------------------------

# Variables
CC = g++
CFLAGS = -c -Wall
LFALGS = -Wall
INCLUDE_DIR = include
SRC_DIR = src
OBJ_DIR = obj
BACKUP_DIR = Backup

# Archivos de Origen
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

# Reglas
all: main

main: $(OBJ_FILES) main.o
	$(CC) $(LFALGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(INCLUDE_DIR) $< -o $@

main.o: main.cpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(INCLUDE_DIR) $< -o $@

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

testing: main
	./main

backup:
	rm -r Backup
	mkdir -p Backup
	cp -r $(SRC_DIR) $(INCLUDE_DIR) main.cpp Backup

clean:
	rm -rf $(OBJ_DIR) main
	rm -rf main.o

.PHONY: all clean
