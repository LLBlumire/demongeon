#include <cstddef>
#include <iostream>

#include "room.hpp"

namespace demon {
    Room::Room() {
        for (std::size_t i = 0; i < 11; ++i) {
            for (std::size_t j = 0; j < 7; ++j) {
                this->tile[i][j] = new tile::Empty();
            }
        }
    }

    Room::~Room() {
        for (std::size_t i = 0; i < 11; ++i) {
            for (std::size_t j = 0; j < 7; ++j) {
                delete this->tile[i][j];
            }
        }
    }

    bool Room::oline(std::ostream* os, int line) {
        if (line < 7 && line >= 0) {
            for (std::size_t x = 0; x < 11; ++x) {
                *os << this->tile[x][line]->render();
            }
            return true;
        } else {
            return false;
        }
    }

    tile::Tile** Room::tile_unchecked(Coord coord) {
        return &this->tile[coord.x][coord.y];
    }
}
