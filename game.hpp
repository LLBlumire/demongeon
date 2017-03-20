#ifndef INCL_GAME_HPP
#define INCL_GAME_HPP

#include "result.hpp"
#include "maze.hpp"
#include "error.hpp"
#include "ending.hpp"

namespace demon {
    class GameState {
        public:
            result::Result<Ending::Enum, Error::Enum>* run();
            GameState();
        protected:
            Maze maze;
    };
}

#endif
