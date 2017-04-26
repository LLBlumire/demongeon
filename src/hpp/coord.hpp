/* coord.hpp
 * Provides the Coord class, an abstraction over discrete natural positions in the cartesian plane.
 */

#ifndef INCL_COORD_HPP
#define INCL_COORD_HPP

#include <cstddef>

namespace demon {
    /* class Coord
     * An abstraction over discrete natural positions in the Cartesian plane.
     */
    class Coord {
        public:
            /* size_t x
             * The x coordinate in the Cartesian plane.
             */
            std::size_t x;

            /* size_t y
             * The y coordinate in the Cartesian plane.
             */
            std::size_t y;

            /* Coord()
             * Default empty constructor.
             */
            Coord() {}

            /* Coord(size_t x, size_t y)
             * Constructs a new Coord with coordinates (x, y).
             */
            Coord(std::size_t x, std::size_t y);

            /* bool operator==(const Coord& other)
             * Compare Equality of two Coord's.
             */
            bool operator==(const Coord& other);

            /* bool operator!=(const Coord& other)
             * Compare Inequality of two Coord's.
             */
            bool operator!=(const Coord& other);
    };

    /* struct coord_compare
     * Provides a strict odering of the Coords. Such that x is used in primary comparison, and y iff x is equal.
     */
    struct coord_compare {
        bool operator() (const Coord& lhs, const Coord& rhs) const;
    };
}

#endif
