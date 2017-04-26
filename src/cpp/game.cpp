#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>

#include "game.hpp"
#include "room.hpp"
#include "direction.hpp"
#include "item.hpp"
#include "tile.hpp"

namespace demon {
    void populate_floor(Maze& maze, Player& player, std::size_t floor) {

        std::vector<Coord> leaf_coords;
        for (std::size_t x = 0; x < 5; ++x) {
            for (std::size_t y = 0; y < 5; ++y) {
                for (std::size_t x_r = 0; x_r < 11; ++x_r) {
                    for (std::size_t y_r = 0; y_r < 7; ++y_r) {
                        delete *maze.room_unchecked(Coord(x, y))->tile_unchecked(Coord(x_r, y_r));
                        *maze.room_unchecked(Coord(x, y))->tile_unchecked(Coord(x_r, y_r)) = new tile::Empty();
                    }
                }

                int edge_count = 0;
                bool** north;
                bool** east;
                bool** south;
                bool** west;
                option::Option<bool*>* nopt = maze.edge(Coord(x, y), Direction::North);
                option::Option<bool*>* eopt = maze.edge(Coord(x, y), Direction::East);
                option::Option<bool*>* sopt = maze.edge(Coord(x, y), Direction::South);
                option::Option<bool*>* wopt = maze.edge(Coord(x, y), Direction::West);
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

        player.coord = Coord(5, 3);
        player.room_coord = player_coord;
        delete *maze.room_unchecked(player_coord)->tile_unchecked(Coord(5,3));
        *maze.room_unchecked(player_coord)->tile_unchecked(Coord(5,3)) = new tile::Player();

        random_index = rand() % leaf_coords.size();
        Coord boss_coord = Coord(leaf_coords[random_index]);
        leaf_coords.erase(leaf_coords.begin()+random_index);

        delete *maze.room_unchecked(boss_coord)->tile_unchecked(Coord(5,3));
        switch (floor) {
            case 1:
                *maze.room_unchecked(boss_coord)->tile_unchecked(Coord(5,3)) = new tile::Enemy(Enemy(EnemyType::D));                
                break;
            case 2:
                *maze.room_unchecked(boss_coord)->tile_unchecked(Coord(5,3)) = new tile::Enemy(Enemy(EnemyType::E));                
                break;
            case 3:
                *maze.room_unchecked(boss_coord)->tile_unchecked(Coord(5,3)) = new tile::Enemy(Enemy(EnemyType::M));                
                break;
            case 4:
                *maze.room_unchecked(boss_coord)->tile_unchecked(Coord(5,3)) = new tile::Enemy(Enemy(EnemyType::O));                
                break;
            case 5:
                *maze.room_unchecked(boss_coord)->tile_unchecked(Coord(5,3)) = new tile::Enemy(Enemy(EnemyType::N));                
                break;
        }

        Coord treasure_coord = Coord(6, 6); // Default Outside map bounds
        if (leaf_coords.size() > 0) {
            random_index = rand() % leaf_coords.size();
            treasure_coord = Coord(leaf_coords[random_index]);
            leaf_coords.erase(leaf_coords.begin()+random_index);

            delete *maze.room_unchecked(treasure_coord)->tile_unchecked(Coord(5,3));
            *maze.room_unchecked(treasure_coord)->tile_unchecked(Coord(5,3)) = new tile::Item(Item((ItemType::Enum)(rand() % 2), (ItemLevel::Enum)(floor-1)));
        }

        for (std::size_t x = 0; x < 5; ++x) {
            for (std::size_t y = 0; y < 5; ++y) {

                if (Coord(x, y) != player_coord && Coord(x, y) != boss_coord && Coord(x, y) != treasure_coord) {
                    for (std::size_t enemy_count = 0; rand() % (enemy_count + 1) == 0; ++enemy_count) {
                        Coord position = Coord(rand() % 11, rand() % 7);
                        delete *maze.room_unchecked(Coord(x, y))->tile_unchecked(position);
                        EnemyType::Enum type;
                        switch (floor) {
                            case 1:
                                switch (rand() % 4) {
                                    case 0:
                                        type = EnemyType::A;
                                        break;
                                    case 1:
                                        type = EnemyType::B;
                                        break;
                                    case 2:
                                        type = EnemyType::C;
                                        break;
                                    case 3:
                                        type = EnemyType::F;
                                        break;
                                }
                                break;
                            case 2:
                                switch (rand() % 4) {
                                    case 0:
                                        type = EnemyType::G;
                                        break;
                                    case 1:
                                        type = EnemyType::H;
                                        break;
                                    case 2:
                                        type = EnemyType::I;
                                        break;
                                    case 3:
                                        type = EnemyType::J;
                                        break;
                                }
                                break;
                            case 3:
                                switch (rand() % 4) {
                                    case 0:
                                        type = EnemyType::K;
                                        break;
                                    case 1:
                                        type = EnemyType::L;
                                        break;
                                    case 2:
                                        type = EnemyType::P;
                                        break;
                                    case 3:
                                        type = EnemyType::Q;
                                        break;
                                }
                                break;
                            case 4:
                                switch (rand() % 4) {
                                    case 0:
                                        type = EnemyType::R;
                                        break;
                                    case 1:
                                        type = EnemyType::S;
                                        break;
                                    case 2:
                                        type = EnemyType::T;
                                        break;
                                    case 3:
                                        type = EnemyType::U;
                                        break;
                                }
                                break;
                            case 5:
                                switch (rand() % 5) {
                                    case 0:
                                        type = EnemyType::V;
                                        break;
                                    case 1:
                                        type = EnemyType::W;
                                        break;
                                    case 2:
                                        type = EnemyType::X;
                                        break;
                                    case 3:
                                        type = EnemyType::Y;
                                        break;
                                    case 4:
                                        type = EnemyType::Z;
                                        break;
                                }
                                break;
                        }
                        *maze.room_unchecked(Coord(x, y))->tile_unchecked(position) = new tile::Enemy(Enemy(type));
                    }
                }
            }
        }
    }


    GameState::GameState() {
        this->floor = 1;
        this->in_menu = false;
        this->player.hp = 100;
        populate_floor(this->maze, this->player, this->floor);
    }

    result::Result<Ending::Enum, Error::Enum>* GameState::run() {
        std::cout << "Welcome, to the DEMONGEON!" << std::endl;

        while (true) {
            // Update the game
            if (!this->in_menu) {
                // Process Attacks
                for (std::size_t x = 0; x < 11; ++x) {
                    for (std::size_t y = 0; y < 7; ++y) {
                        tile::Tile** source = this->maze.room_unchecked(this->player.room_coord)->tile_unchecked(Coord(x, y));
                        Enemy* enemy;
                        if (source[0]->let_enemy(enemy)) {
                            if (enemy->attack(this->player.coord, Coord(x, y))) {
                                std::size_t damage = (std::size_t)((20.0 * (double)(enemy->damage)) / (20.0 + (this->player.shield.stat)));
                                if (damage > this->player.hp) {
                                    return new result::Ok<Ending::Enum, Error::Enum>(Ending::Died);
                                }
                                this->player.hp = this->player.hp - damage;
                                std::cout << "Took " << damage << " damage!" << std::endl;
                            }
                        }
                    }
                }

                // Process Moves
                std::vector<Coord> move_targets;
                for (std::size_t x = 0; x < 11; ++x) {
                    for (std::size_t y = 0; y < 7; ++y) {
                        tile::Tile** source = this->maze.room_unchecked(this->player.room_coord)->tile_unchecked(Coord(x, y));
                        Enemy* enemy;
                        if (source[0]->let_enemy(enemy)) {
                            Coord dest = enemy->move_ai(this->player.coord, Coord(x, y));
                            tile::Tile** target = this->maze.room_unchecked(this->player.room_coord)->tile_unchecked(dest);
                            if (target[0]->is_empty() && !(std::find(move_targets.begin(), move_targets.end(), Coord(x, y)) != move_targets.end())) {
                                delete *target;
                                *target = *source;
                                *source = new tile::Empty();
                                move_targets.push_back(dest);
                            }
                        }
                    }
                }
            }

            int line = 0;
            bool done = false;
            // Render the Game
            std::cout << "HP: " << this->player.hp << std::endl;
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
                std::cout << "Sword: " << this->player.sword.to_string() << std::endl;
                std::cout << "Shield: " << this->player.shield.to_string() << std::endl;
                std::cout << "Items [" << this->player.items.size() << "]" << std::endl;
                std::size_t idx = 0;
                for (std::vector<Item>::iterator i = this->player.items.begin(); i != this->player.items.end(); i++) {
                    std::cout << "\t" << idx << ": " << i->to_string() << std::endl;
                    ++idx;
                }
                idx = 0;
                std::cout << "Gemstones [" << this->player.gemstones.size() << "]" << std::endl;
                for (std::vector<Gemstone::Enum>::iterator i = this->player.gemstones.begin(); i != this->player.gemstones.end(); i++) {
                    std::cout << "\t" << idx << ": " << gemstone_string(*i) << std::endl;
                    ++idx;
                }
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

            if (!this->in_menu) {
                // Process Directional Input
                if (input == "w" || (input == "W" && room_empty)) {
                    if (this->player.coord.y == 0 || input == "W") {
                        if(this->player.coord.x == 5 || input == "W") {
                            if (*this->maze.edge_unchecked(Coord(this->player.room_coord), Direction::North) && !(this->player.room_coord.y == 0)) {
                                delete *this->maze.room_unchecked(this->player.room_coord)->tile_unchecked(this->player.coord);
                                *this->maze.room_unchecked(this->player.room_coord)->tile_unchecked(this->player.coord) = new tile::Empty();
                                this->player.coord = Coord(5, 6);
                                --this->player.room_coord.y;
                                delete *this->maze.room_unchecked(this->player.room_coord)->tile_unchecked(this->player.coord);
                                *this->maze.room_unchecked(this->player.room_coord)->tile_unchecked(this->player.coord) = new tile::Player();
                            }
                        }
                    } else {
                        if (this->maze.room_unchecked(this->player.room_coord)->tile_unchecked(Coord(this->player.coord.x, this->player.coord.y - 1))[0]->is_empty()) { 
                            delete *this->maze.room_unchecked(this->player.room_coord)->tile_unchecked(this->player.coord);
                            *this->maze.room_unchecked(this->player.room_coord)->tile_unchecked(this->player.coord) = new tile::Empty();
                            --this->player.coord.y;
                            delete *this->maze.room_unchecked(this->player.room_coord)->tile_unchecked(this->player.coord);
                            *this->maze.room_unchecked(this->player.room_coord)->tile_unchecked(this->player.coord) = new tile::Player();
                        }
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
                        if (this->maze.room_unchecked(this->player.room_coord)->tile_unchecked(Coord(this->player.coord.x - 1, this->player.coord.y))[0]->is_empty()) { 
                            delete* this->maze.room_unchecked(this->player.room_coord)->tile_unchecked(this->player.coord);
                            *this->maze.room_unchecked(this->player.room_coord)->tile_unchecked(this->player.coord) = new tile::Empty();
                            --this->player.coord.x;
                            delete* this->maze.room_unchecked(this->player.room_coord)->tile_unchecked(this->player.coord);
                            *this->maze.room_unchecked(this->player.room_coord)->tile_unchecked(this->player.coord) = new tile::Player();
                        }
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
                        if (this->maze.room_unchecked(this->player.room_coord)->tile_unchecked(Coord(this->player.coord.x, this->player.coord.y + 1))[0]->is_empty()) {
                            delete* this->maze.room_unchecked(this->player.room_coord)->tile_unchecked(this->player.coord);
                            *this->maze.room_unchecked(this->player.room_coord)->tile_unchecked(this->player.coord) = new tile::Empty();
                            ++this->player.coord.y;
                            delete* this->maze.room_unchecked(this->player.room_coord)->tile_unchecked(this->player.coord);
                            *this->maze.room_unchecked(this->player.room_coord)->tile_unchecked(this->player.coord) = new tile::Player();
                        }
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
                        if (this->maze.room_unchecked(this->player.room_coord)->tile_unchecked(Coord(this->player.coord.x + 1, this->player.coord.y))[0]->is_empty()) {
                            delete* this->maze.room_unchecked(this->player.room_coord)->tile_unchecked(this->player.coord);
                            *this->maze.room_unchecked(this->player.room_coord)->tile_unchecked(this->player.coord) = new tile::Empty();
                            ++this->player.coord.x;
                            delete* this->maze.room_unchecked(this->player.room_coord)->tile_unchecked(this->player.coord);
                            *this->maze.room_unchecked(this->player.room_coord)->tile_unchecked(this->player.coord) = new tile::Player();
                        }
                    }
                }

                // Process Directional Attack Input
                option::Option<Coord>* target_coord_opt = new option::None<Coord>();
                if (input == "xw" && this->player.coord.y != 0) {
                    delete target_coord_opt;
                    target_coord_opt = new option::Some<Coord>(Coord(this->player.coord.x, this->player.coord.y - 1));
                } else if (input == "xa" && this->player.coord.x != 0) {
                    delete target_coord_opt;
                    target_coord_opt = new option::Some<Coord>(Coord(this->player.coord.x - 1, this->player.coord.y));
                } else if (input == "xs" && this->player.coord.y != 6) {
                    delete target_coord_opt;
                    target_coord_opt = new option::Some<Coord>(Coord(this->player.coord.x, this->player.coord.y + 1));
                } else if (input == "xd" && this->player.coord.x != 10) {
                    delete target_coord_opt;
                    target_coord_opt = new option::Some<Coord>(Coord(this->player.coord.x + 1, this->player.coord.y));
                }
                Coord* coord;
                if (target_coord_opt->let_some(coord)) {
                    tile::Tile** target = this->maze.room_unchecked(this->player.room_coord)->tile_unchecked(*coord);
                    Enemy* enemy;
                    Item* item;
                    if (target[0]->let_enemy(enemy)) {
                        std::size_t damage = this->player.sword.stat;
                        if (damage > enemy->hp) {
                            Gemstone::Enum rand_gemstone; // Forward Declare because switch case does not create scope.

                            switch (enemy->on_death()) {
                                case OnDeath::Heal:
                                    this->player.hp = this->player.hp + (std::size_t)(((float)enemy->original_hp) / ((float)((rand() % 4) + 1))) + 1;
                                    break;
                                case OnDeath::RandomGemstone:
                                    rand_gemstone = (Gemstone::Enum)(rand() % 7);
                                    this->player.gemstones.push_back(rand_gemstone);
                                    std::cout << "Found " << gemstone_string(rand_gemstone) << "!" << std::endl;
                                    break;
                                case OnDeath::BossClear:
                                    ++this->floor;
                                    this->maze.generate();
                                    populate_floor(this->maze, this->player, this->floor);
                                    break;
                                case OnDeath::Win:
                                    return new result::Ok<Ending::Enum, Error::Enum>(Ending::Win);
                            }
                            delete *target;
                            *target = new tile::Empty();
                        } else {
                            enemy->hp = enemy->hp - damage;
                            std::cout << "Dealt " << damage << " damage!" << std::endl;
                        }
                    } else if (target[0]->let_item(item)) {
                        this->player.items.push_back(*item);
                        delete *target;
                        *target = new tile::Empty();
                    }
                }
                delete target_coord_opt;

            } else {
                if (input == "e") {
                    bool cancelled = false;
                    std::size_t gem_index;
                    while (true) {
                        std::cout << "Enter Gem To Socket: ";
                        std::cin >> gem_index;
                        if (std::cin.fail()) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            cancelled = true;
                            break;
                        } else {
                            if (gem_index >= this->player.gemstones.size()) {
                                cancelled = true;
                            }
                            break;
                        }
                    }
                    if (cancelled) {
                        std::cout << "Gem Socketing Cancelled" << std::endl;
                    } else {
                        std::cout << "Sword (W) or Shield? (A): ";
                        std::string sword_shield;
                        std::cin >> sword_shield;
                        if (sword_shield == "W" || sword_shield == "w") {
                            if (this->player.sword.socket(this->player.gemstones[gem_index])) {
                                this->player.gemstones.erase(this->player.gemstones.begin() + gem_index);
                            }
                        } else if (sword_shield == "A" || sword_shield == "a") {
                            if (this->player.shield.socket(this->player.gemstones[gem_index])) {
                                this->player.gemstones.erase(this->player.gemstones.begin() + gem_index);
                            }
                        }
                    }
                }
                if (input == "q") {
                    bool cancelled = false;
                    std::size_t item_index;
                    while (true) {
                        std::cout << "Enter Item To Swap: ";
                        std::cin >> item_index;
                        if (std::cin.fail()) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            cancelled = true;
                            break;
                        } else {
                            if (item_index >= this->player.items.size()) {
                                cancelled = true;
                            }
                            break;
                        }
                    }
                    if (cancelled) {
                        std::cout << "Item Swapping Cancelled" << std::endl;
                    } else {
                        Item item = this->player.items[item_index];
                        if (item.type == ItemType::Sword) {
                            this->player.items[item_index] = this->player.sword;
                            this->player.sword = item;
                        } else if (item.type == ItemType::Shield) {
                            this->player.items[item_index] = this->player.shield;
                            this->player.shield = item;
                        }
                    }
                }
            }

            if (input == "i") {
                this->in_menu = !this->in_menu;
            }
        }

        return new result::Err<Ending::Enum, Error::Enum>(Error::UnexpectedLoopTermination);
    }
}
