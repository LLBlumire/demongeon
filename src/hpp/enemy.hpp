#ifndef INCL_ENEMY_HPP
#define INCL_ENEMY_HPP

namespace demon {
    namespace EnemyType {
        enum Enum {
            A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z
        };
    }
    class Enemy {
        public:
            char symbol;
            Enemy(EnemyType::Enum type);
            Enemy(){};
    };
}

#endif