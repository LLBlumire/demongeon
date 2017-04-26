/* ending.hpp
 * Provides the Ending enum, representing the three possible ending states of the game.
 */

#ifndef INCL_ENDING_HPP
#define INCL_ENDING_HPP

namespace demon {
    /* enum Ending
     * Represents the three possible ending states of the game.
     */
    namespace Ending {
        enum Enum {
            /* Win
             * The player has won the game by killing the final boss.
             */
            Win,

            /* Died
             * The player was killed
             */
            Died,

            /* Quit
             * The player exited the game
             */
            Quit
        };
    }
}

#endif
