#ifndef INCL_ENEMY_HPP
#define INCL_ENEMY_HPP

#include "coord.hpp"

namespace demon {
    namespace EnemyType {
        enum Enum {
            A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z
        };
    }

    namespace OnDeath {
        enum Enum {
            Heal,
            RandomGemstone,
            BossClear,
            Win
        };
    }

    class Enemy {
        public:
            char symbol;
            std::size_t hp;
            std::size_t original_hp;
            std::size_t damage;
            EnemyType::Enum type;
            Enemy(EnemyType::Enum type);
            Enemy(){};
            Coord move_ai(Coord player, Coord self);
            OnDeath::Enum on_death();
            bool attack(Coord player, Coord self);
    };
}

#endif