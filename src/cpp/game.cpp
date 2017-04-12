#include <iostream>
#include <sstream>

#include "game.hpp"

namespace demon {
    GameState::GameState() {
        this->maze = Maze();
        this->player = Player();
    }

    result::Result<Ending::Enum, Error::Enum>* GameState::run() {
        std::cout << "Welcome, to the DEMONGEON!" << std::endl;

        int line = 0;
        bool done = false;
        while (!done) {
            done = false;
            {
                int maze_line = line;
                std::stringstream ss;
                done = done || !this->maze.oline(&ss, maze_line);
                std::string line = ss.str();
                if (maze_line / 2 == this->player.room_y && maze_line % 2 == 0) {
                    line[this->player.room_x * 2] = '@';
                }
                std::cout << line;
            }
            if (!done) std::cout << std::endl;
            ++line;
        }

        return new result::Ok<Ending::Enum, Error::Enum>(Ending::Win);
    }
}
