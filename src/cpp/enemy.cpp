#include <cstdlib>

#include "enemy.hpp"
#include "item.hpp"

namespace demon {
    Enemy::Enemy(EnemyType::Enum type) {
        this->symbol = type + 'A';
        this->type = type;
        std::size_t type_num = (std::size_t)type;
        if (type_num < 'G' - 'A') {
            // First Floor
            this->hp = dice(7, 6);
            this->damage = dice(2, 6);
        } else if (type_num < 'K' - 'A') {
            // Second Floor
            this->hp = dice(7, 8);
            this->damage = dice(2, 8);
        } else if (type_num < 'R' - 'A') {
            // Third Floor
            this->hp = dice(7, 10);
            this->damage = dice(2,10);
        } else if (type_num < 'V' - 'A') {
            // Fourth Floor
            this->hp = dice(7, 12);
            this->damage = dice(2, 12);
        } else {
            // Fifth Floor
            this->hp = dice(7, 20);
            this->damage = dice(2, 20);
        }
        if (type == EnemyType::D) {
            // First Floor Boss
            this->hp = 55;
            this->damage = 15;
        } else if (type == EnemyType::E) {
            // Second Floor Boss
            this->hp = 70;
            this->damage = 20;
        } else if (type == EnemyType::M) {
            // Third Floor Boss
            this->hp = 85;
            this->damage = 25;
        } else if (type == EnemyType::O) {
            // Fourth Floor Boss
            this->hp = 100;
            this->damage = 30;
        } else if (type == EnemyType::N) {
            // Fifth Floor Boss
            this->hp = 250;
            this->damage = 70;
        }
        this->original_hp = this->hp;
    }

    Coord Enemy::move_ai(Coord player, Coord self) {
        if (player.x == self.x) {
            if (player.y > self.y) {
                return Coord(self.x, self.y + 1);
            } else {
                return Coord(self.x, self.y - 1);
            }
        } else if (player.y == self.y) {
            if (player.x > self.x) {
                return Coord(self.x + 1, self.y);
            } else {
                return Coord(self.x - 1, self.y);
            }
        } else {
            if (rand() % 2 == 0) {
                if (player.y > self.y) {
                    return Coord(self.x, self.y + 1);
                } else {
                    return Coord(self.x, self.y - 1);
                }
            } else {
                if (player.x > self.x) {
                    return Coord(self.x + 1, self.y);
                } else {
                    return Coord(self.x - 1, self.y);
                }
            }
        }
    }

    OnDeath::Enum Enemy::on_death() {
        if (this->type == EnemyType::D || this->type == EnemyType::E || this->type == EnemyType::M || this->type == EnemyType::O) {
            return OnDeath::BossClear;
        } else if (this->type == EnemyType::N) {
            return OnDeath::Win;
        } else if (rand() % 20 == 0) {
            return OnDeath::RandomGemstone;
        } else {
            return OnDeath::Heal;
        }
    }

    bool Enemy::attack(Coord player, Coord self) {
        if (player.x == self.x) {
            if (player.y == (self.y + 1) || player.y == (self.y - 1)) {
                return true;
            }
        } else if (player.y == self.y) {
            if (player.x == (self.x + 1) || player.x == (self.x - 1)) {
                return true;
            }
        }
        return false;
    }
}