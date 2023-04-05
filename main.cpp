#include <iostream>

#include <chrono>
#include <thread>

#include "Grid.h"
#include "EnemyGrid.h"

using namespace std;
using namespace nure;

void clearConsole()
{
    std::cout << "\033[2J";    // Clear the console
    std::cout << "\033[0;0H";  // Move the cursor to the top-left corner
}

ostream& displayDocs(ostream& os)
{
    return os << ANSI_COLOR_WHITE << "* - Empty" << ANSI_COLOR_RESET << ", " << ANSI_COLOR_WHITE
              << "? - Unknown" << ANSI_COLOR_RESET << ", " << ANSI_COLOR_GREEN << "S - Ship"
              << ANSI_COLOR_RESET << ", " << ANSI_COLOR_PURPLE << "M - Missed" << ANSI_COLOR_RESET
              << ", " << ANSI_COLOR_RED << "X - Hit" << ANSI_COLOR_RESET << ", " << ANSI_COLOR_BLUE
              << "X - Sunk" << ANSI_COLOR_RESET << endl
              << endl;
}

int main(int argc, char* argv[])
{
    srand(time(nullptr));

    Grid my_grid;
    EnemyGrid enemy_grid;

    my_grid.generateRandomMap();
    enemy_grid.generateRandomMap();

    bool my_turn = true;

    while (!my_grid.isGameOver() && !enemy_grid.isGameOver()) {
        clearConsole();
        displayDocs(cout);
        cout << "Your board:" << endl << my_grid << endl;
        cout << std::setw(MAP_WIDTH * 2 + 2) << std::setfill('-') << "" << endl << endl;
        cout << "Computer's board:" << endl << enemy_grid << endl;

        if (my_turn) {
            Location hit_location;
            cin >> hit_location;

            State state = enemy_grid.getState(hit_location);
            if (state != State::Hit && state != State::Miss && state != State::Dead) {
                enemy_grid.hit(hit_location);

                State new_state = enemy_grid.getState(hit_location);
                if (new_state == State::Miss) {
                    my_turn = false;
                }
            }
        } else {
            Location hit_location = my_grid.calculateHitLocation();

            State state = my_grid.getState(hit_location);

            if (state != State::Hit && state != State::Miss && state != State::Dead) {
                my_grid.hit(hit_location);

                State new_state = my_grid.getState(hit_location);
                if (new_state == State::Miss) {
                    my_turn = true;
                }
            }
        }
    }

    cout << (my_grid.isGameOver() ? "Computer Won!" : "You Won!") << endl;

    return 0;
}
