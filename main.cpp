#include <iostream>

#include <chrono>
#include <thread>

#include "Player.h"

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

    Player* players[] = {new UserPlayer(), new ComputerPlayer()};
    int current_player = 1;

    while (!players[0]->is_lost() && !players[1]->is_lost()) {
        Player* player = players[current_player];

        clearConsole();
        displayDocs(cout);

        cout << "Your board:" << endl;
        players[0]->display(cout);
        cout << std::setw(MAP_WIDTH * 2 + 2) << std::setfill('-') << "" << endl << endl;
        cout << "Computer's board:" << endl;
        players[1]->display(cout);

        if (player->hit() == State::Miss) {
            current_player = (current_player + 1) % 2;
        }
    }

    cout << (players[0]->is_lost() ? "Computer Won!" : "You Won!") << endl;

    return 0;
}
