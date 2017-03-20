#include <cstdlib>

#include "maze.hpp"

typedef std::set<demon::Coord, demon::coord_compare> CoordSet;

namespace demon {

    Maze::Maze() {
        for (std::size_t x = 0; x < 5; ++x) {
            for (std::size_t y = 0; y < 5; ++y) {
                this->rooms[x][y] = Room();
            }
        }
        for (std::size_t i = 0; i < 2; ++i) {
            for (std::size_t j = 0; j < 4; ++j) {
                for (std::size_t k = 0; k < 5; ++k) {
                    this->edges[i][j][k] = false;
                }
            }
        }

        // Create a set of rooms (tracked by pointer) to mark all that have been
        // included in the maze.
        CoordSet joined = CoordSet();

        // Insert the middle room.
        joined.insert(Coord(2, 2));

        // Until all nodes have been joined.
        while (joined.size() < 25) {

            // Find already joined cell.
            Coord random_joined_coord;
            while (true) {
                random_joined_coord = Coord(rand() % 5, rand() % 5);
                CoordSet::iterator seeker = joined.find(random_joined_coord);
                if (seeker != joined.end()) {
                    break;
                }
            }

            // Find valid direction.
            std::size_t attempts = 0;
            Direction::Enum dir;
            Coord target;
            bool found = true;
            while (true) {
                dir = (Direction::Enum)(rand() % 4);
                int dx = dx_dir(dir);
                int dy = dy_dir(dir);
                target = Coord(random_joined_coord.x + dx,
                               random_joined_coord.y + dy);
                if (target.x < 5 && target.y < 5) {
                    target = Coord(random_joined_coord.x + dx,
                                   random_joined_coord.y + dy);
                    CoordSet::iterator seeker = joined.find(target);
                    if (seeker == joined.end()) {
                        break;
                    }
                }
                ++attempts;
                // Mean time to have randommed every direction is 8.33...
                if (attempts == 9) {
                    found = false;
                    break;
                }
            }

            // If a valid direction was found.
            if (found) {
                optional::Option<bool*>* edge_opt = this->edge(random_joined_coord, dir);
                bool* edge;
                if (edge_opt->unwrap_some(&edge)) {
                    *edge = true;
                    joined.insert(target);
                }
                delete edge_opt;
            }

        }

    }

    optional::Option<Room*>* Maze::room(Coord c) {
        if (c.x < 5 || c.y < 5) {
            return new optional::Some<Room*>(&this->rooms[c.x][c.y]);
        } else {
            return new optional::None<Room*>();
        }
    }

    Room* Maze::room_unchecked(Coord c) {
        return &this->rooms[c.x][c.y];
    }

    optional::Option<bool*>* Maze::edge(Coord c, Direction::Enum dir) {
        std::size_t i;
        std::size_t j;
        std::size_t k;
        room_to_edge(c.x, c.y, dir, i, j, k);
        if (i < 2 && j < 4 && k < 5) {
            return new optional::Some<bool*>(&this->edges[i][j][k]);
        } else {
            return new optional::None<bool*>();
        }
    }

    bool* Maze::edge_unchecked(Coord c, Direction::Enum dir) {
        std::size_t i;
        std::size_t j;
        std::size_t k;
        room_to_edge(c.x, c.y, dir, i, j, k);
        return &this->edges[i][j][k];
    }

    bool Maze::oline(std::ostream* os, int line) {
        if (line < 9) {
            if (line % 2 == 0) {
                for (std::size_t x = 0; x < 5; ++x) {
                    *os << "+";
                    optional::Option<bool*>* edge_opt = this->edge(Coord(x, line / 2),
                                                        Direction::East);
                    bool* edge;
                    if (edge_opt->unwrap_some(&edge) && *edge) {
                        *os << "-";
                    } else {
                        *os << " ";
                    }
                    delete edge_opt;
                }
            } else {
                for (std::size_t x = 0; x < 5; ++x) {
                    optional::Option<bool*>* edge_opt = this->edge(Coord(x, (line - 1) / 2),
                                                        Direction::South);
                    bool* edge;
                    if (edge_opt->unwrap_some(&edge) && *edge) {
                        *os << "|";
                    } else {
                        *os << " ";
                    }
                    *os << " ";
                }
            }
            return true;
        } else {
            return false;
        }

    }


    void room_to_edge(std::size_t x, std::size_t y, Direction::Enum dir,
                      std::size_t& i, std::size_t& j, std::size_t& k) {
        switch (dir) {
            case Direction::North:
                i = 1;
                j = y - 1;
                k = x;
                break;
            case Direction::East:
                i = 0;
                j = x;
                k = y;
                break;
            case Direction::South:
                i = 1;
                j = y;
                k = x;
                break;
            case Direction::West:
                i = 0;
                j = x - 1;
                k = y;
                break;
        }
    }

    void room_to_edge(Coord coord, Direction::Enum dir, std::size_t& i,
                      std::size_t& j, std::size_t k) {
        room_to_edge(coord.x, coord.y, dir, i, j, k);
    }

    void edge_to_room(std::size_t i, std::size_t j, std::size_t k, int dir,
                      std::size_t& x, std::size_t& y) {
        if (i == 0) {
            if (dir >= 0) {
                x = j + 1;
                y = k;
            } else {
                x = j;
                y = k;
            }
        } else {
            if (dir >= 0) {
                x = k;
                y = j + 1;
            } else {
                x = k;
                y = j;
            }
        }
    }

    void edge_to_room(std::size_t i, std::size_t j, std::size_t k, int dir,
                      Coord& coord) {
        edge_to_room(i, j, k, dir, coord.x, coord.y);
    }

    int dx_dir(Direction::Enum dir) {
        switch (dir) {
            case Direction::North:
                return 0;
            case Direction::South:
                return 0;
            case Direction::East:
                return 1;
            case Direction::West:
                return -1;
        }
    }
    int dy_dir(Direction::Enum dir) {
        switch (dir) {
            case Direction::West:
                return 0;
            case Direction::East:
                return 0;
            case Direction::South:
                return 1;
            case Direction::North:
                return -1;
        }
    }
}
