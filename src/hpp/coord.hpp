#ifndef INCL_COORD_HPP
#define INCL_COORD_HPP

#include <cstddef>

namespace demon {
    class Coord {
        public:
            std::size_t x;
            std::size_t y;
            Coord();
            Coord(std::size_t x, std::size_t y);
            bool operator==(const Coord& other);
            bool operator!=(const Coord& other);
    };

    struct coord_compare {
        bool operator() (const Coord& lhs, const Coord& rhs) const;
    };
}

#endif
