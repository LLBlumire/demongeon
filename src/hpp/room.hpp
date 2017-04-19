#ifndef INCL_ROOM_HPP
#define INCL_ROOM_HPP

#include "tile.hpp"

namespace demon {
    class Room {
        public:
            Room();
            ~Room();
            tile::Tile* tile[11][7]; // Owned
            bool oline(std::ostream* os, int line);
            tile::Tile** tile_unchecked(Coord coord);
    };
}

#endif
