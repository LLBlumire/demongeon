/* maze.hpp
 * Provides the Maze class, a representation of a square lattice graph.
 */

#ifndef INCL_MAZE_HPP
#define INCL_MAZE_HPP

#include <cstddef>
#include <iostream>
#include <set>

#include "coord.hpp"
#include "direction.hpp"
#include "option.hpp"
#include "room.hpp"

namespace demon {
    /* class Maze
     * A represenation of a 5 by 5 square lattice graph
     */
    class Maze {
        public:
            /* Room rooms
             * The 5 by 5 grid of rooms (x, y).
             */
            Room rooms[5][5];

            /* bool edges
             * The grid of edges, (i, j, k), where i is marks north-south or east-west, and (j, k) represents the 4 by 5 grid of the coordinate space.
             */
            bool edges[2][4][5];

            /* Maze()
             * Constructs and Generates a Maze.
             */
            Maze();

            /* Option<Room*>* room(Coord c)
             * Get a room at coordinates, Some<Room*> if in bounds, None if out of bounds.
             */
            option::Option<Room*>* room(Coord c);

            /* Room* room_unchecked(Coord c)
             * Get a room at coordinates.
             */
            Room* room_unchecked(Coord c);

            /* Option<bool*>* edge(Coord c, Direction dir)
             * Get an edge at coordinates in a direction. Some<bool*> if in bounds, None if out of bounds.
             */
            option::Option<bool*>* edge(Coord c, Direction::Enum dir);

            /* bool* edge_unchecked(Coord c, Direction dir)
             * Get an edge at coordinates in a direction.
             */
            bool* edge_unchecked(Coord c, Direction::Enum dir);

            /* bool oline(ostream* os, int line)
             * Get a line of output for displaying.
             */
            bool oline(std::ostream* os, int line);

            /* void generate()
             * Generate a new maze.
             */
            void generate();
    };

    /* void room_to_edge(size_t x, size_t y, Direction dir, size_t& i, size_t& j, size_t& k)
     * Converts room coordinates and a direction to edge coordinates.
     */
    void room_to_edge(std::size_t x, std::size_t y, Direction::Enum dir,
                      std::size_t& i, std::size_t& j, std::size_t& k);

    /* void room_to_edge(Coord coord, Direction dir, size_t& i, size_t& j, size_t& k)
     * Converts room coordinates and a direction to edge coordinates.
     */
    void room_to_edge(Coord coord, Direction::Enum dir, std::size_t& i,
                      std::size_t& j, std::size_t& k);

    /* void edge_to_room(size_t i, size_t j, size_t k, int dir, size_t& x, size_t& y)
     * Converts edge coordinates and a direction (-1 or 1) to edge coordinates.
     */
    void edge_to_room(std::size_t i, std::size_t j, std::size_t k, int dir,
                      std::size_t& x, std::size_t& y);
    /* void edge_to_room(size_t i, size_t j, size_t k, int dir, Coord& coord)
     * Converts edge coordinates and a direction (-1 or 1) to edge coordinates.
     */
    void edge_to_room(std::size_t i, std::size_t j, std::size_t k, int dir,
                      Coord& coord);

    /* int dx_dir(Direction dir)
     * Convets a Direction into an x component (1, 0, -1).
     */
    int dx_dir(Direction::Enum dir);

    /* int dy_dir(Direction dir)
     * Converts a Direction into a y component (1, 0, -1).
     */
    int dy_dir(Direction::Enum dir);

}

#endif
