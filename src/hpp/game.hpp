#ifndef INCL_GAME_HPP
#define INCL_GAME_HPP

#include <cstddef>

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
            std::size_t floor;
            bool in_menu;
    };
}

#endif
