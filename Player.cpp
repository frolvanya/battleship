#include "Player.h"

using namespace std;

namespace nure {
    bool Player::is_lost() const { return grid.isGameOver(); }

    UserPlayer::UserPlayer() { grid.generateRandomMap(); }

    State UserPlayer::hit()
    {
        Location hit_location = grid.calculateHitLocation();

        State state = grid.getState(hit_location);
        if (state != State::Hit && state != State::Miss && state != State::Dead) {
            grid.hit(hit_location);

            state = grid.getState(hit_location);
        }

        return state;
    }

    ostream& UserPlayer::display(ostream& os) const
    {
        if (grid.getError()) {
            os << grid.getError() << endl;
        } else {
            os << "   A B C D E F G H I J" << endl;
            for (int i = 0; i < MAP_HEIGHT; i++) {
                os << std::setw(2) << std::setfill(' ') << i + 1 << " ";
                for (int j = 0; j < MAP_WIDTH; j++) {
                    switch (grid.getState(Location(j, i))) {
                        case State::Empty:
                            os << ANSI_COLOR_WHITE << "* " << ANSI_COLOR_RESET;
                            break;
                        case State::Occupied:
                            os << ANSI_COLOR_GREEN << "S " << ANSI_COLOR_RESET;
                            break;
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
                            os << " ";
                            break;
                    }
                }

                os << endl;
            }

            os << endl;
        }

        return os;
    }

    ComputerPlayer::ComputerPlayer() { grid.generateRandomMap(); }

    State ComputerPlayer::hit()
    {
        Location hit_location;
        cin >> hit_location;

        State state = grid.getState(hit_location);
        if (state != State::Hit && state != State::Miss && state != State::Dead) {
            grid.hit(hit_location);

            state = grid.getState(hit_location);
        }

        return state;
    }

    ostream& ComputerPlayer::display(ostream& os) const
    {
        if (grid.getError()) {
            os << grid.getError() << endl;
        } else {
            os << "   A B C D E F G H I J" << endl;
            for (int i = 0; i < MAP_HEIGHT; i++) {
                os << std::setw(2) << std::setfill(' ') << i + 1 << " ";
                for (int j = 0; j < MAP_WIDTH; j++) {
                    switch (grid.getState(Location(j, i))) {
                        case State::Empty:
                        case State::Occupied:
                            os << ANSI_COLOR_WHITE << "? " << ANSI_COLOR_RESET;
                            break;
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
                            os << " ";
                            break;
                    }
                }

                os << endl;
            }

            os << endl;
        }

        return os;
    }

}  // namespace nure
