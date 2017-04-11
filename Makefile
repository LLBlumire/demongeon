BUILD = build
OBJ = $(BUILD)/obj
BIN = $(BUILD)/bin
SOURCE = src
CPP = $(SOURCE)/cpp
HPP = $(SOURCE)/hpp
STP = $(SOURCE)/stp
CC = clang++ -Wall -I$(HPP) -std=c++03
LL = $(CC) -o $(BIN)/demongeon
CPPSTP := $(shell command -v cppstp 2>/dev/null)

.PHONY: default
default: $(OBJ)/main.o $(OBJ)/game.o $(OBJ)/coord.o $(OBJ)/maze.o $(OBJ)/room.o
	$(LL) $(OBJ)/main.o $(OBJ)/game.o $(OBJ)/coord.o $(OBJ)/maze.o $(OBJ)/room.o

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

.PHONY: stp
stp: $(STP)/option.stp.toml $(STP)/result.stp.toml
ifndef CPPSTP
	$(error "cppstp is not available")
endif
	$(CPPSTP) $(STP)/option.stp.toml > $(HPP)/option.hpp
	$(CPPSTP) $(STP)/result.stp.toml > $(HPP)/result.hpp

.PHONY: clean
clean:
	rm -f $(OBJ)/*

.PHONY: clean-stp
clean-stp:
	rm -f $(HPP)/result.hpp $(HPP)/option.hpp