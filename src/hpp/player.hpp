/* player.hpp
 * Provides the Player Class which represents the playable protagonist in the game world.
 */

#ifndef INCL_PLAYER_HPP
#define INCL_PLAYER_HPP

#include <cstddef>
#include <vector>

#include "coord.hpp"
#include "item.hpp"

namespace demon {
    /* class Player
     * Represents the playable protagonist in the game world.
     */
    class Player {
        public:
            /* Coord coord
             * The coordinates of the player in the room they are in.
             */
            Coord coord;

            /* Coord room_coord
             * The coordinates of the room the player is in, in the maze.
             */
            Coord room_coord;

            /* size_t hp
             * The current health of the player.
             */
            std::size_t hp;

            /* vector<Gemstone> gemstones
             * The Gemstones held by the player.
             */
            std::vector<Gemstone::Enum> gemstones;

            /* vector<Item> items
             * The Items held by the player.
             */
            std::vector<Item> items;

            /* Item sword
             * The sword equipped by the player.
             */
            Item sword;

            /* Item shield
             * The shield equipped by the player.
             */
            Item shield;

            /* Player()
             * Constructs the player with default values.
             */
            Player();

            /* Player(size_t x, size_t y, size_t room_x, size_t room_y, size_t hp)
             * Construct a player from values.
             */
            Player(
                std::size_t x,
                std::size_t y,
                std::size_t room_x,
                std::size_t room_y,
                std::size_t hp
            );
            /* Player(Coord coord, Coord room_coord, size_t hp)
             * Construct a player from coordinate values.
             */
            Player(
                Coord coord,
                Coord room_coord,
                std::size_t hp
            );
    };
}

#endif