/* room.hpp
 * Contains the Room class, which represents a single room in the maze.
 */

#ifndef INCL_ROOM_HPP
#define INCL_ROOM_HPP

#include "tile.hpp"

namespace demon {
    /* class Room
     * Represents a single room in the maze.
     */
    class Room {
        public:
            /* Room()
             * Construct an empty room.
             */
            Room();

            /* ~Room()
             * Clear memory and deconstruct room.
             */
            ~Room();

            /* Tile* tile[11][7]
             * All the Tiles in the room. To be treated as owned.
             */
            tile::Tile* tile[11][7]; // Owned

            /* bool oline(ostream* os, int line)
             * Get a line of output for displaying.
             */
            bool oline(std::ostream* os, int line);

            /* Tile** tile_unchecked(Coord coord)
             * Get a tile from coordinates.
             */
            tile::Tile** tile_unchecked(Coord coord);
    };
}

#endif
