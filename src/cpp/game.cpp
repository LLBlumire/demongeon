#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>

#include "game.hpp"
#include "room.hpp"
#include "direction.hpp"

namespace demon {
    GameState::GameState() {
        std::vector<Coord> leaf_coords;
        this->in_menu = false;
        for (std::size_t x = 0; x < 5; ++x) {
            for (std::size_t y = 0; y < 5; ++y) {
                int edge_count = 0;
                bool** north;
                bool** east;
                bool** south;
                bool** west;
                option::Option<bool*>* nopt = this->maze.edge(Coord(x, y), Direction::North);
                option::Option<bool*>* eopt = this->maze.edge(Coord(x, y), Direction::East);
                option::Option<bool*>* sopt = this->maze.edge(Coord(x, y), Direction::South);
                option::Option<bool*>* wopt = this->maze.edge(Coord(x, y), Direction::West);
                if (nopt->let_some(north) && **north) {
                    ++edge_count;
                }
                if (eopt->let_some(east) && **east) {
                    ++edge_count;
                }
                if (sopt->let_some(south) && **south) {
                    ++edge_count;
                }
                if (wopt->let_some(west) && **west) {
                    ++edge_count;
                }
                delete nopt;
                delete eopt;
                delete sopt;
                delete wopt;
                if (edge_count == 1) {
                    leaf_coords.push_back(Coord(x, y));
                }
            }
        }

        std::size_t random_index = rand() % leaf_coords.size();
        Coord player_coord = Coord(leaf_coords[random_index]);
        leaf_coords.erase(leaf_coords.begin()+random_index);

        this->player = Player(Coord(5,3), player_coord, 100);
        delete *this->maze.room_unchecked(player_coord)->tile_unchecked(Coord(5,3));
        *this->maze.room_unchecked(player_coord)->tile_unchecked(Coord(5,3)) = new tile::Player();

        random_index = rand() % leaf_coords.size();
        Coord boss_coord = Coord(leaf_coords[random_index]);
        leaf_coords.erase(leaf_coords.begin()+random_index);

        delete *this->maze.room_unchecked(boss_coord)->tile_unchecked(Coord(5,3));
        *this->maze.room_unchecked(boss_coord)->tile_unchecked(Coord(5,3)) = new tile::Enemy(Enemy(EnemyType::D));
        std::cout << "Boss:" << boss_coord.x << "," << boss_coord.y << std::endl;

        random_index = rand() % leaf_coords.size();
        Coord treasure_coord = Coord(leaf_coords[random_index]);
        leaf_coords.erase(leaf_coords.begin()+random_index);


    }

    result::Result<Ending::Enum, Error::Enum>* GameState::run() {
        std::cout << "Welcome, to the DEMONGEON!" << std::endl;

        while (true) {
            int line = 0;
            bool done = false;
            // Render the Game
            if (!this->in_menu) {
                while (!done) {
                    done = true;
                    { // Render the Map
                        int maze_line = line;
                        std::stringstream ss;
                        done = !this->maze.oline(&ss, maze_line) && done;
                        std::string ostr = ss.str();
                        if (maze_line >= 0 && (std::size_t)maze_line / 2 == this->player.room_coord.y && maze_line % 2 == 0) {
                            ostr[this->player.room_coord.x * 2] = '@';
                        }
                        std::cout << ostr;
                    }
                    { // Render the Room
                        int room_line = line - 1;
                        Room* room = this->maze.room_unchecked(this->player.room_coord);
                        bool north = *this->maze.edge_unchecked(Coord(this->player.room_coord), Direction::North);
                        bool south = *this->maze.edge_unchecked(Coord(this->player.room_coord), Direction::South);
                        bool east = *this->maze.edge_unchecked(Coord(this->player.room_coord), Direction::East);
                        bool west = *this->maze.edge_unchecked(Coord(this->player.room_coord), Direction::West);
                        if (this->player.room_coord.x == 4) {
                            east = false;
                        }
                        if (this->player.room_coord.x == 0) {
                            west = false;
                        }
                        if (this->player.room_coord.y == 4) {
                            south = false;
                        }
                        if (this->player.room_coord.y == 0) {
                            north = false;
                        }
                        std::stringstream ss;
                        if (room_line == -1) {
                            ss << "/----";
                            if (north) {
                                ss << "| |";
                            } else {
                                ss << "---";
                            }
                            ss << "----\\";
                            done = false && done;
                        } else if (room_line == 7) {
                            ss << "\\----";
                            if (south) {
                                ss << "| |";
                            } else {
                                ss << "---";
                            }
                            ss << "----/";
                            done = false && done;
                        } else if (room_line > -1 && room_line < 7) {
                            if ((room_line == 2 || room_line == 4) && west) {
                                ss << "-";
                            } else if (room_line == 3 && west) {
                                ss << " ";
                            } else {
                                ss << "|";
                            }
                            done = !room->oline(&ss, room_line) && done;
                            if ((room_line == 2 || room_line == 4) && east) {
                                ss << "-";
                            } else if (room_line == 3 && east) {
                                ss << " ";
                            } else {
                                ss << "|";
                            }
                        }
                        std::cout << ss.str();
                    }
                    
                    if (!done) std::cout << std::endl;
                    ++line;
                }
            } else {
                // Render the inventory
                
            }

            // Render the UI
            std::cout << ">>> ";
            std::string input;
            std::cin >> input;

            // Process Inputs
            if (input == ":quit" || input == "Z") {
                return new result::Ok<Ending::Enum, Error::Enum>(Ending::Quit);
            }

            // Generate Flag for Fast Movement
            bool room_empty = true;
            for (std::size_t x = 0; x < 11; ++x) {
                for (std::size_t y = 0; y < 7; ++y) {
                    if ((*this->maze.room_unchecked(this->player.room_coord)->tile_unchecked(Coord(x,y)))->is_enemy()) {
                        room_empty = false;
                    }
                }
            }

            // Process Directional Input
            if (input == "w" || (input == "W" && room_empty)) {
                if (this->player.coord.y == 0 || input == "W") {
                    if(this->player.coord.x == 5 || input == "W") {
                        if (*this->maze.edge_unchecked(Coord(this->player.room_coord), Direction::North) && !(this->player.room_coord.y == 0)) {
                            delete* this->maze.room_unchecked(this->player.room_coord)->tile_unchecked(this->player.coord);
                            *this->maze.room_unchecked(this->player.room_coord)->tile_unchecked(this->player.coord) = new tile::Empty();
                            this->player.coord = Coord(5, 6);
                            --this->player.room_coord.y;
                            delete* this->maze.room_unchecked(this->player.room_coord)->tile_unchecked(this->player.coord);
                            *this->maze.room_unchecked(this->player.room_coord)->tile_unchecked(this->player.coord) = new tile::Player();
                        }
                    }
                } else {
                    delete* this->maze.room_unchecked(this->player.room_coord)->tile_unchecked(this->player.coord);
                    *this->maze.room_unchecked(this->player.room_coord)->tile_unchecked(this->player.coord) = new tile::Empty();
                    --this->player.coord.y;
                    delete* this->maze.room_unchecked(this->player.room_coord)->tile_unchecked(this->player.coord);
                    *this->maze.room_unchecked(this->player.room_coord)->tile_unchecked(this->player.coord) = new tile::Player();
                }
            }
            if (input == "a" || (input == "A" && room_empty)) {
                if (this->player.coord.x == 0 || input == "A") {
                    if(this->player.coord.y == 3 || input == "A") {
                        if (*this->maze.edge_unchecked(Coord(this->player.room_coord), Direction::West) && !(this->player.room_coord.x == 0)) {
                            delete* this->maze.room_unchecked(this->player.room_coord)->tile_unchecked(this->player.coord);
                            *this->maze.room_unchecked(this->player.room_coord)->tile_unchecked(this->player.coord) = new tile::Empty();
                            this->player.coord = Coord(10, 3);
                            --this->player.room_coord.x;
                            delete* this->maze.room_unchecked(this->player.room_coord)->tile_unchecked(this->player.coord);
                            *this->maze.room_unchecked(this->player.room_coord)->tile_unchecked(this->player.coord) = new tile::Player();
                        }
                    }
                } else {
                    delete* this->maze.room_unchecked(this->player.room_coord)->tile_unchecked(this->player.coord);
                    *this->maze.room_unchecked(this->player.room_coord)->tile_unchecked(this->player.coord) = new tile::Empty();
                    --this->player.coord.x;
                    delete* this->maze.room_unchecked(this->player.room_coord)->tile_unchecked(this->player.coord);
                    *this->maze.room_unchecked(this->player.room_coord)->tile_unchecked(this->player.coord) = new tile::Player();
                }
            }
            if (input == "s" || (input == "S" && room_empty)) {
               if (this->player.coord.y == 6 || input == "S") {
                    if(this->player.coord.x == 5 || input == "S") {
                       if (*this->maze.edge_unchecked(Coord(this->player.room_coord), Direction::South) && !(this->player.room_coord.y == 4)) {
                           delete* this->maze.room_unchecked(this->player.room_coord)->tile_unchecked(this->player.coord);
                            *this->maze.room_unchecked(this->player.room_coord)->tile_unchecked(this->player.coord) = new tile::Empty();
                            this->player.coord = Coord(5, 0);
                            ++this->player.room_coord.y;
                            delete* this->maze.room_unchecked(this->player.room_coord)->tile_unchecked(this->player.coord);
                            *this->maze.room_unchecked(this->player.room_coord)->tile_unchecked(this->player.coord) = new tile::Player();
                        }
                    }
                } else {
                    delete* this->maze.room_unchecked(this->player.room_coord)->tile_unchecked(this->player.coord);
                    *this->maze.room_unchecked(this->player.room_coord)->tile_unchecked(this->player.coord) = new tile::Empty();
                    ++this->player.coord.y;
                    delete* this->maze.room_unchecked(this->player.room_coord)->tile_unchecked(this->player.coord);
                    *this->maze.room_unchecked(this->player.room_coord)->tile_unchecked(this->player.coord) = new tile::Player();
                }
            }
            if (input == "d" || (input == "D" && room_empty)) {
               if (this->player.coord.x == 10 || input == "D") {
                    if(this->player.coord.y == 3 || input == "D") {
                       if (*this->maze.edge_unchecked(Coord(this->player.room_coord), Direction::East) && !(this->player.room_coord.x == 4)) {
                           delete* this->maze.room_unchecked(this->player.room_coord)->tile_unchecked(this->player.coord);
                            *this->maze.room_unchecked(this->player.room_coord)->tile_unchecked(this->player.coord) = new tile::Empty();
                            this->player.coord = Coord(0, 3);
                            ++this->player.room_coord.x;
                            delete* this->maze.room_unchecked(this->player.room_coord)->tile_unchecked(this->player.coord);
                            *this->maze.room_unchecked(this->player.room_coord)->tile_unchecked(this->player.coord) = new tile::Player();
                        }
                    }
                } else {
                    delete* this->maze.room_unchecked(this->player.room_coord)->tile_unchecked(this->player.coord);
                    *this->maze.room_unchecked(this->player.room_coord)->tile_unchecked(this->player.coord) = new tile::Empty();
                    ++this->player.coord.x;
                    delete* this->maze.room_unchecked(this->player.room_coord)->tile_unchecked(this->player.coord);
                    *this->maze.room_unchecked(this->player.room_coord)->tile_unchecked(this->player.coord) = new tile::Player();
                }
            }
        }

        return new result::Ok<Ending::Enum, Error::Enum>(Ending::Win);
    }
}
