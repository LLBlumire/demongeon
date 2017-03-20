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
    };

    struct coord_compare {
        bool operator() (const Coord& lhs, const Coord& rhs) const;
    };
}

#endif
