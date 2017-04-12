#include "player.hpp"

namespace demon {
    Player::Player() {
        this->x = 0;
        this->y = 0;
        this->room_x = 0;
        this->room_y = 0;
        this->hp = 0;
    }
    Player::Player(
        std::size_t x,
        std::size_t y,
        std::size_t room_x,
        std::size_t room_y,
        std::size_t hp
    ) {
        this->x = x;
        this->y = y;
        this->room_x = room_x;
        this->room_y = room_y;
        this->hp = hp;
    }
}