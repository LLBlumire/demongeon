#include <iostream>

#include "coord.hpp"

namespace demon {
    Coord::Coord() {}

    Coord::Coord(std::size_t x, std::size_t y) {
        this->x = x;
        this->y = y;
    }

    bool Coord::operator==(const Coord& other) {
        return (this->x == other.x) && (this->y == other.y);
    }
    
    bool Coord::operator!=(const Coord& other) {
        return !(*this == other);
    }

    bool coord_compare::operator() (const Coord& lhs, const Coord& rhs) const {
        if (lhs.x < rhs.x) {
            return true;
        } else if (lhs.x == rhs.x) {
            return lhs.y < rhs.y;
        } else {
            return false;
        }
    }
    
}
