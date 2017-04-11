# Directory Structure
BUILD = build # Output Directory
OBJ = $(BUILD)/obj # Object Directory
BIN = $(BUILD)/bin # Binary Directory
SOURCE = src # Input Directory
CPP = $(SOURCE)/cpp # C++ Files
HPP = $(SOURCE)/hpp # C++ Header Files
STP = $(SOURCE)/stp # C++ Sum Type Generator Files

# Try clang++, fallback to g++
CPP = clang++
ifeq (, $(shell command -v clang++ 2>/dev/null))
CPP := g++
endif

# Build And Link Commands
CC = $(CPP) -Wall -I$(HPP) -std=c++03
LL = $(CC) -o $(BIN)/demongeon

# C++ Sum Type Generator Compiler
CPPSTP := $(shell command -v cppstp 2>/dev/null)

# Build Executable
.PHONY: default
default: $(OBJ)/main.o $(OBJ)/game.o $(OBJ)/coord.o $(OBJ)/maze.o $(OBJ)/room.o
	$(LL) $(OBJ)/main.o $(OBJ)/game.o $(OBJ)/coord.o $(OBJ)/maze.o $(OBJ)/room.o

# Build Object Files
$(OBJ)/main.o: $(CPP)/main.cpp
	$(CC) -c $(CPP)/main.cpp -o $(OBJ)/main.o

$(OBJ)/game.o: $(CPP)/game.cpp
	$(CC) -c $(CPP)/game.cpp -o $(OBJ)/game.o

$(OBJ)/coord.o: $(CPP)/coord.cpp
	$(CC) -c $(CPP)/coord.cpp -o $(OBJ)/coord.o

$(OBJ)/maze.o: $(CPP)/maze.cpp
	$(CC) -c $(CPP)/maze.cpp -o $(OBJ)/maze.o

$(OBJ)/room.o: $(CPP)/room.cpp
	$(CC) -c $(CPP)/room.cpp -o $(OBJ)/room.o

# Build Sum Type Header Files
.PHONY: stp
stp: $(STP)/option.stp.toml $(STP)/result.stp.toml
ifndef CPPSTP
	$(error "cppstp is not available")
endif
	$(CPPSTP) $(STP)/option.stp.toml > $(HPP)/option.hpp
	$(CPPSTP) $(STP)/result.stp.toml > $(HPP)/result.hpp

# Remove Object Files
.PHONY: clean
clean:
	rm -f $(OBJ)/*

# Remove Generated Sum Type Header Files
.PHONY: clean-stp
clean-stp:
	rm -f $(HPP)/result.hpp $(HPP)/option.hpp