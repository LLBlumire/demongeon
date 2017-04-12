#include <iostream>

#include "game.hpp"

namespace demon {
    GameState::GameState() {}

    result::Result<Ending::Enum, Error::Enum>* GameState::run() {
        std::cout << "Welcome, to the DEMONGEON!" << std::endl;

        int line = 0;
        bool done = false;
        while (!done) {
            done = false;
            done = done || !this->maze.oline(&std::cout, line);
            if (!done) std::cout << std::endl;
            ++line;
        }

        return new result::Ok<Ending::Enum, Error::Enum>(Ending::Win);
    }
}
