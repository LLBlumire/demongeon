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
    class Maze {
        public:
            Room rooms[5][5];
            bool edges[2][4][5];
            Maze();
            option::Option<Room*>* room(Coord c);
            Room* room_unchecked(Coord c);
            option::Option<bool*>* edge(Coord c, Direction::Enum dir);
            bool* edge_unchecked(Coord c, Direction::Enum dir);
            bool oline(std::ostream* os, int line);
            void generate();
    };

    void room_to_edge(std::size_t x, std::size_t y, Direction::Enum dir,
                      std::size_t& i, std::size_t& j, std::size_t& k);

    void room_to_edge(Coord coord, Direction::Enum dir, std::size_t& i,
                      std::size_t& j, std::size_t& k);

    void edge_to_room(std::size_t i, std::size_t j, std::size_t k, int dir,
                      std::size_t& x, std::size_t& y);

    void edge_to_room(std::size_t i, std::size_t j, std::size_t k, int dir,
                      Coord& coord);

    int dx_dir(Direction::Enum dir);

    int dy_dir(Direction::Enum dir);

}

#endif
