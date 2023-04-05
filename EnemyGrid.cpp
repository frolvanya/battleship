#include "EnemyGrid.h"

using namespace std;

namespace nure {
    EnemyGrid::EnemyGrid() { setEmpty(); }

    ostream& EnemyGrid::display(ostream& os) const
    {
        if (error) {
            os << error << endl;
        } else {
            os << "   A B C D E F G H I J" << endl;
            for (int i = 0; i < MAP_HEIGHT; i++) {
                os << std::setw(2) << std::setfill(' ') << i + 1 << " ";
                for (int j = 0; j < MAP_WIDTH; j++) {
                    switch (grid[i][j]) {
                        case State::Empty:
                        case State::Occupied:
                            os << ANSI_COLOR_WHITE << "? " << ANSI_COLOR_RESET;
                            break;
                        // case State::Occupied:
                        //     os << ANSI_COLOR_GREEN << "S " << ANSI_COLOR_RESET;
                        //     break;
                        case State::Hit:
                            os << ANSI_COLOR_RED << "X " << ANSI_COLOR_RESET;
                            break;
                        case State::Dead:
                            os << ANSI_COLOR_BLUE << "X " << ANSI_COLOR_RESET;
                            break;
                        case State::Miss:
                            os << ANSI_COLOR_PURPLE << "M " << ANSI_COLOR_RESET;
                            break;
                        default:
                            os << grid[i][j] << " ";
                            break;
                    }
                }

                os << endl;
            }
        }

        return os;
    }

    ostream& operator<<(ostream& os, const EnemyGrid& rhs) { return rhs.display(os); }

}  // namespace nure
