# Linker
CC=g++

# Files
FILES=\
	  main.cpp \
	  game.cpp \
	  maze.cpp \
	  room.cpp \
	  coord.cpp

# C++ Version
CVERS=c++03

.PHONEY : all
all : demongeon 

fresh : clean demongeon

demongeon : $(FLIES)
	$(CC) $(FILES) -std=$(CVERS) -o demongeon

.PHONY : clean
clean :
	rm demongeon.exe
