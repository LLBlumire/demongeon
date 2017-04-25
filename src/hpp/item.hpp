#ifndef INCL_ITEM_HPP
#define INCL_ITEM_HPP

#include <cstddef>
#include <vector>
#include <string>

namespace demon {
    namespace ItemType {
        enum Enum {
            Sword,
            Shield
        };
    }
    namespace ItemLevel {
        enum Enum {
            Inferior,
            Lesser,
            Neutral,
            Greater,
            Superior
        };
    }
    namespace Gemstone {
        enum Enum {
            Demonic,
            Swift,
            Hardy,
            Lucky,
            Enraged,
            Burning,
            Frozen
        };
    }
    class Item {
        public:
            ItemType::Enum type;
            ItemLevel::Enum level;
            std::size_t socket_size;
            std::vector<Gemstone::Enum> gemstones;
            std::size_t stat;
            Item(){};
            Item(ItemType::Enum type, ItemLevel::Enum level);
            std::string to_string();
            bool socket(Gemstone::Enum gemstone);
    };

    std::string gemstone_string(Gemstone::Enum gemstone);
    std::string item_type_string(ItemType::Enum item_type);
    std::string item_level_string(ItemLevel::Enum item_level);

    std::size_t dice(std::size_t count, std::size_t max);
}

#endif