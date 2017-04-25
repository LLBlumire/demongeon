#include "player.hpp"

namespace demon {
    Player::Player() {
        this->coord = Coord(0, 0);
        this->room_coord = Coord(0, 0);
        this->hp = 100;
        this->sword = Item(ItemType::Sword, ItemLevel::Inferior);
        this->shield = Item(ItemType::Shield, ItemLevel::Inferior);
    }
    
    Player::Player(
        std::size_t x,
        std::size_t y,
        std::size_t room_x,
        std::size_t room_y,
        std::size_t hp
    ) {
        *this = Player(Coord(x, y), Coord(room_x, room_y), hp);
    }

    Player::Player(
        Coord coord,
        Coord room_coord,
        std::size_t hp
    ) {
        this->coord = coord;
        this->room_coord = room_coord;
        this->hp = hp;
        this->sword = Item(ItemType::Sword, ItemLevel::Inferior);
        this->shield = Item(ItemType::Shield, ItemLevel::Inferior);
    }
}