#ifndef INCL_PLAYER_HPP
#define INCL_PLAYER_HPP

#include <cstddef>

namespace demon {
    class Player {
        public:
            std::size_t x;
            std::size_t y;
            std::size_t room_x;
            std::size_t room_y;
            std::size_t hp;
            Player();
            Player(
                std::size_t x,
                std::size_t y,
                std::size_t room_x,
                std::size_t room_y,
                std::size_t hp
            );
    };
}

#endif