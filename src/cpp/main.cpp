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
    int exit_code = 0;

    GameState game;

    result::Result<Ending::Enum, Error::Enum>* game_result = game.run();
    {
        Ending::Enum* ending;
        Error::Enum* error;
        if (game_result->let_ok(ending)) {
            switch (*ending) {
                case Ending::Win:
                    std::cout << "You Win!";
                    break;
                case Ending::Died:
                    std::cout << "Try Again Next Time!";
                    break;
                case Ending::Quit:
                    std::cout << "Play Again Soon!";
            }
        } else if (game_result->let_err(error)) {
            switch (*error) {
                case Error::Unknown:
                    std::cout << "An Unknown Error Occured";
                    break;
            }

            exit_code = 1;
        }
    }
    delete game_result;

    std::cout << std::endl;

    return exit_code;
}
