// Standard Includes
#include <cstdlib>
#include <ctime>
#include <iostream>

// Game Includes
#include "game.hpp"

using namespace demon;

int main() {
    // Initialize RNG
    srand(time(NULL));

    GameState game = GameState();

    result::Result<Ending::Enum, Error::Enum>* game_result = game.run();
    if (game_result->is_ok()) {
        Ending::Enum ending;
        game_result->unwrap_ok(&ending);

        switch (ending) {
            case Ending::Win:
                std::cout << "You Win!";
                break;
            case Ending::Died:
                std::cout << "Try Again Next Time!";
                break;
        }
    }
    delete game_result;

    std::cout << std::endl;
}
