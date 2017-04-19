#ifndef INCL_PLAYER_HPP
#define INCL_PLAYER_HPP

#include <cstddef>
#include <vector>

#include "coord.hpp"
#include "item.hpp"

namespace demon {
    class Player {
        public:
            Coord coord;
            Coord room_coord;
            std::size_t hp;
            std::vector<Gemstone::Enum> gemstones;
            std::vector<Item> items;
            Item sword;
            Item shield;
            Player();
            Player(
                std::size_t x,
                std::size_t y,
                std::size_t room_x,
                std::size_t room_y,
                std::size_t hp
            );
            Player(
                Coord coord,
                Coord room_coord,
                std::size_t hp
            );
    };
}

#endif