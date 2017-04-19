#include "enemy.hpp"

namespace demon {
    Enemy::Enemy(EnemyType::Enum type) {
        this->symbol = type + 'A';
    }
}