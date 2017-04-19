#ifndef INCL_ITEM_HPP
#define INCL_ITEM_HPP

#include <cstddef>
#include <vector>

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
    };
}

#endif