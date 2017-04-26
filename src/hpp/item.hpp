/* item.hpp
 * Provides various interfaces for working with Items.
 */
#ifndef INCL_ITEM_HPP
#define INCL_ITEM_HPP

#include <cstddef>
#include <vector>
#include <string>

namespace demon {
    /* enum ItemType
     * Represents the possible types an Item can be.
     */
    namespace ItemType {
        enum Enum {
            Sword,
            Shield
        };
    }
    
    /* enum ItemLevel
     * Represents the possible qualities an Item can have.
     */
    namespace ItemLevel {
        enum Enum {
            Inferior,
            Lesser,
            Neutral,
            Greater,
            Superior
        };
    }

    /* enum Gemstone
     * Represents potential buffs that can be applied to an Item
     */
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

    /* class Item
     * Represents an instance of an item that can be on the floor or held by a player.
     */
    class Item {
        public:
            /* ItemType type
             * The type of the item, and thus where it is held.
             */
            ItemType::Enum type;

            /* ItemLevel level
             * The quality of the item, and an indicator of it's stats.
             */
            ItemLevel::Enum level;

            /* size_t socket_size
             * The number of gemstone sockets available on an item.
             */
            std::size_t socket_size;

            /* vector<Gemstone> gemstones
             * The gemstones socketed to the item.
             */
            std::vector<Gemstone::Enum> gemstones;

            /* size_t stat
             * The stat of the weapon, attack value if a sword, defense if a shield.
             */
            std::size_t stat;

            /* Item()
             * Default empty constructor.
             */
            Item(){};

            /* Item(ItemType type, Itemlevel level)
             * Constructs a new Item from it's type an level.
             */
            Item(ItemType::Enum type, ItemLevel::Enum level);

            /* string to_string()
             * Converts the Item to a string representation.
             */
            std::string to_string();

            /* bool socket(Gemstone gemstone)
             * Attempts to add a gemstone to an item.
             */
            bool socket(Gemstone::Enum gemstone);
    };

    /* string gemstone_string(Gemstone gemstone)
     * Converts a Gemstone to a string representation.
     */
    std::string gemstone_string(Gemstone::Enum gemstone);

    /* string item_type_string(ItemType item_type)
     * Converts an ItemType to a string representation.
     */
    std::string item_type_string(ItemType::Enum item_type);

    /* string item_level_string(ItemLevel item_level)
     * Converts an ItemLevel to a string representation.
     */
    std::string item_level_string(ItemLevel::Enum item_level);

    /* size_t dice(size_t count, size_t max)
     * Rolls count, max sided dice, and sums the results
     */
    std::size_t dice(std::size_t count, std::size_t max);
}

#endif