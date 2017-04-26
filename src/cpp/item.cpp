#include <sstream>
#include <cstdlib>

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

    std::string gemstone_string(Gemstone::Enum gemstone) {
        switch (gemstone) {
            case Gemstone::Demonic:
                return std::string("Demonic");
            case Gemstone::Swift:
                return std::string("Swift");
            case Gemstone::Hardy:
                return std::string("Hardy");
            case Gemstone::Lucky:
                return std::string("Lucky");
            case Gemstone::Enraged:
                return std::string("Enraged");
            case Gemstone::Burning:
                return std::string("Burning");
            case Gemstone::Frozen:
                return std::string("Frozen");
            default:
                return std::string("");
        }
    }

    std::string item_type_string(ItemType::Enum item_type) {
        switch (item_type) {
            case ItemType::Sword:
                return std::string("Sword");
            case ItemType::Shield:
                return std::string("Shield");
            default:
                return std::string("");
        }
    }

    std::string item_level_string(ItemLevel::Enum item_level) {
        switch (item_level) {
            case ItemLevel::Inferior:
                return std::string("Inferior");
            case ItemLevel::Lesser:
                return std::string("Lesser");
            case ItemLevel::Neutral:
                return std::string("");
            case ItemLevel::Greater:
                return std::string("Greater");
            case ItemLevel::Superior:
                return std::string("Superior");
            default:
                return std::string("");
        }
    }

    std::string Item::to_string() {
        std::stringstream ss;
        ss << item_level_string(this->level) << " ";
        for (std::vector<Gemstone::Enum>::iterator i = this->gemstones.begin(); i != this->gemstones.end(); i++) {
            ss << gemstone_string(*i) << " ";
        }
        ss << item_type_string(this->type) << " ";
        ss << "(" << this->stat << ") ";
        ss << "[" << this->gemstones.size() << "/" << this->socket_size << "]";
        return ss.str();
    }

    bool Item::socket(Gemstone::Enum gemstone) {
        if (this->gemstones.size() <= this->socket_size) {
            this->gemstones.push_back(gemstone);
            return true;
        } else {
            return false;
        }
    }
}