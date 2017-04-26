/* game.hpp
 * Provides the GameState class, which stores the complete state of the game.
 */

#ifndef INCL_GAME_HPP
#define INCL_GAME_HPP

#include <cstddef>
#include <algorithm>

#include "result.hpp"
#include "maze.hpp"
#include "error.hpp"
#include "ending.hpp"
#include "player.hpp"

namespace demon {
    /* class GameState
     * Stores the complete state of the game
     */
    class GameState {
        public:
            /* Result<Ending, Error>* run()
             * Runs the game. Returns Ok(_) if the game is ended gracefully, Err(_) if it is not.
             */
            result::Result<Ending::Enum, Error::Enum>* run();

            /* GameState()
             * Constructor, fully creates a new game in it's default state.
             */
            GameState();
        protected:
            /* Maze maze
             * The maze currently being explored.
             */
            Maze maze;

            /* Player player
             * The protagonist of the game.
             */
            Player player;

            /* size_t floor
             * The current floor the player is on, values 1 to 5.
             */
            std::size_t floor;

            /* bool in_menu
             * Whether or not the player has the menu open.
             */
            bool in_menu;
    };
}

#endif
