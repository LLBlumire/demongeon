#include <iostream>

#include "game.hpp"

namespace demon {
    GameState::GameState() {}
    result::Result<Ending::Enum, Error::Enum>* GameState::run() {
        std::cout << "Welcome, to the DEMONGEON!" << std::endl;

        for (int i = 0; this->maze.oline(&std::cout, i); ++i) {
            std::cout << std::endl;
        }

        return new result::Ok<Ending::Enum, Error::Enum>(Ending::Win);
    }
}
