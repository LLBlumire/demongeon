#include "item.hpp"

namespace demon {
    std::size_t dice(std::size_t count, std::size_t max) {
        std::size_t acc = 0;
        for (std::size_t i = 0; i < count; ++i) {
            acc = acc + (rand() % max) + 1;
        }
        return acc;
    }
    Item::Item(ItemType::Enum type, ItemLevel::Enum level) {
        this->type = type;
        this->level = level;
        switch (level) {
            case ItemLevel::Inferior:
                this->socket_size = dice(1, 6) + 1;
                if (type == ItemType::Sword) {
                    this->stat = dice(3, 6) + 3;
                } else if (type == ItemType::Shield) {
                    this->stat = dice(2, 6) + 4;
                }
                break;
            case ItemLevel::Lesser:
                this->socket_size = dice(1, 8) + 2;
                if (type == ItemType::Sword) {
                    this->stat = dice(3, 8) + 5;
                } else if (type == ItemType::Shield) {
                    this->stat = dice(2, 8) + 6;
                }
                break;
            case ItemLevel::Neutral:
                this->socket_size = dice(1, 10) + 3;
                if (type == ItemType::Sword) {
                    this->stat = dice(3, 10) + 7;
                } else if (type == ItemType::Shield) {
                    this->stat = dice(2, 10) + 8;
                }
                break;
            case ItemLevel::Greater:
                this->socket_size = dice(1, 12) + 4;
                if (type == ItemType::Sword) {
                    this->stat = dice(3, 12) + 9;
                } else if (type == ItemType::Shield) {
                    this->stat = dice(2, 12) + 10;
                }
                break;
            case ItemLevel::Superior:
                this->socket_size = dice(1, 20) + 5;
                if (type == ItemType::Sword) {
                    this->stat = dice(3, 20) + 17;
                } else if (type == ItemType::Shield) {
                    this->stat = dice(2, 20) + 18;
                }
                break;
        }
    }
}