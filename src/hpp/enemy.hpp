/* enemy.hpp
 * Provides the EnemyType, and OnDeath enums, and the Enemy class. Represents things to do with processing enemies in the game.
 */

#ifndef INCL_ENEMY_HPP
#define INCL_ENEMY_HPP

#include "coord.hpp"

namespace demon {
    /* enum EnemyType
     * Represents the possible types of enemies in the game.
     */
    namespace EnemyType {
        enum Enum {
            A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z
        };
    }

    /* enum OnDeath
     * Represents the event that should occur when an enemy is killed.
     */
    namespace OnDeath {
        enum Enum {
            /* Heal
             * Give the player a portion of the enemies max HP as health.
             */
            Heal,

            /* RandomGemstone
             * Give the player a random gemstone.
             */
            RandomGemstone,

            /* BossClear
             * Generate a new floor.
             */
            BossClear,

            /* Win
             * Exit the game with a Win status.
             */
            Win
        };
    }

    /* class Enemy
     * Represents an instance of an Enemy in the game.
     */
    class Enemy {
        public:
            /* char symbol
             * The Character used to represent the Enemy.
             */
            char symbol;

            /* size_t hp
             * The current HP of the Enemy.
             */
            std::size_t hp;

            /* size_t original_hp
             * The starting HP of the Enemy (before any damage).
             */
            std::size_t original_hp;

            /* size_t damage
             * The damage the Enemy deals.
             */
            std::size_t damage;

            /* EnemyType type
             * The type of the Enemy.
             */
            EnemyType::Enum type;
            
            /* Enemy()
             * Default empty constructor.
             */
            Enemy(){};

            /* Enemy(EnemyType type)
             * Constructs a new Enemy of a specific type.
             */
            Enemy(EnemyType::Enum type);

            /* Coord move_ai(Coord player, Coord self)
             * Calculates the Coordinate this enemy would like to move to.
             */
            Coord move_ai(Coord player, Coord self);

            /* OnDeath on_death()
             * Runs on Enemy Death and represents what should happen after their death.
             */
            OnDeath::Enum on_death();

            /* bool attack(Coord player, Coord self)
             * Calculates whether or not the enemy is in range to attack.
             */
            bool attack(Coord player, Coord self);
    };
}

#endif