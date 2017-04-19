#ifndef INCL_GAME_HPP
#define INCL_GAME_HPP

#include "result.hpp"
#include "maze.hpp"
#include "error.hpp"
#include "ending.hpp"
#include "player.hpp"

namespace demon {
    class GameState {
        public:
            result::Result<Ending::Enum, Error::Enum>* run();
            GameState();
        protected:
            Maze maze;
            Player player;
            bool in_menu;
    };
}

#endif
