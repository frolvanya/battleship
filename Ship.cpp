#include <limits>

#include "Grid.h"
#include "Ship.h"

using namespace std;

namespace nure {
    Location::Location() : x(-1), y(-1) {}
    Location::Location(int tmp_x, int tmp_y) : x(-1), y(-1)
    {
        if (isValid(tmp_x, tmp_y)) {
            x = tmp_x;
            y = tmp_y;
        }
    }

    Location& Location::generateRandomLocation()
    {
        x = std::rand() % MAP_WIDTH;
        y = std::rand() & MAP_HEIGHT;

        return *this;
    }

    bool Location::isValid(int tmp_x, int tmp_y) const
    {
        return tmp_x >= 0 && tmp_y >= 0 && tmp_x < MAP_WIDTH && tmp_y < MAP_HEIGHT;
    }
    Location::operator bool() const { return isValid(x, y); }
    Location& Location::operator=(const Location& tmp_location)
    {
        x = tmp_location.x;
        y = tmp_location.y;

        return *this;
    }

    istream& Location::read(istream& is)
    {
        Location tmp_location;

        cout << "Enter location (e.g A1)\n> ";

        while (!tmp_location) {
            char tmp_x;
            int tmp_y;

            if (is >> tmp_x >> tmp_y) {
                int parsed_x;
                switch (tmp_x) {
                    case 'a':
                    case 'A':
                        parsed_x = 0;
                        break;
                    case 'b':
                    case 'B':
                        parsed_x = 1;
                        break;
                    case 'c':
                    case 'C':
                        parsed_x = 2;
                        break;
                    case 'd':
                    case 'D':
                        parsed_x = 3;
                        break;
                    case 'e':
                    case 'E':
                        parsed_x = 4;
                        break;
                    case 'f':
                    case 'F':
                        parsed_x = 5;
                        break;
                    case 'g':
                    case 'G':
                        parsed_x = 6;
                        break;
                    case 'h':
                    case 'H':
                        parsed_x = 7;
                        break;
                    case 'i':
                    case 'I':
                        parsed_x = 8;
                        break;
                    case 'j':
                    case 'J':
                        parsed_x = 9;
                        break;
                    default:
                        parsed_x = -1;
                        break;
                }

                tmp_location = Location(parsed_x, tmp_y - 1);
            } else {
                is.clear();
                is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

            if (!tmp_location) {
                cout << INVALID_LOCATION << endl << "> ";
            }
        }

        operator=(tmp_location);

        return is;
    }

    ostream& Location::display(ostream& os) const { return os << "(" << x << ";" << y << ")"; }

    Ship& Ship::setInvalid()
    {
        location = Location();
        direction = Direction::Invalid;
        deck = -1;

        return *this;
    }

    Ship::Ship(int tmp_deck)
    {
        setInvalid();

        if (tmp_deck > 0 && tmp_deck < 5) {
            generateRandomShip();
            deck = tmp_deck;
        }
    }
    Ship::Ship(Location tmp_location, Direction tmp_direction, int tmp_deck)
    {
        setInvalid();

        if (tmp_location && tmp_deck > 0 && tmp_deck < 5) {
            location = tmp_location;
            direction = tmp_direction;
            deck = tmp_deck;
        }
    }

    Ship& Ship::generateRandomShip()
    {
        location.generateRandomLocation();

        int direction_index = std::rand() % 4;
        switch (direction_index) {
            case 0:
                direction = Direction::Up;
                break;
            case 1:
                direction = Direction::Right;
                break;
            case 2:
                direction = Direction::Down;
                break;
            case 3:
                direction = Direction::Left;
                break;
            default:
                break;
        }

        return *this;
    }

    Ship::operator bool() const { return direction != Direction::Invalid && deck != -1; }

    Location Ship::getLocation() const { return location; }
    Location Ship::getEndLocation()
    {
        Location end_location = location;

        switch (direction) {
            case Direction::Up:
                end_location.y -= deck - 1;
                break;
            case Direction::Down:
                end_location.y += deck - 1;
                break;
            case Direction::Left:
                end_location.x -= deck - 1;
                break;
            case Direction::Right:
                end_location.x += deck - 1;
                break;
            case Direction::Invalid:
                end_location = Location();
                break;
        }

        if (location.x > end_location.x) {
            int tmp = location.x;
            location.x = end_location.x;
            end_location.x = tmp;

            direction = Direction::Right;
        } else if (location.y > end_location.y) {
            int tmp = location.y;
            location.y = end_location.y;
            end_location.y = tmp;

            direction = Direction::Down;
        }

        return end_location;
    }
    Direction Ship::getDirection() const { return direction; }
    int Ship::getDeck() const { return deck; }

    std::ostream& operator<<(std::ostream& os, const Direction& rhs)
    {
        switch (rhs) {
            case Direction::Up:
                os << "UP";
                break;
            case Direction::Down:
                os << "DOWN";
                break;
            case Direction::Left:
                os << "LEFT";
                break;
            case Direction::Right:
                os << "Right";
                break;
            case Direction::Invalid:
                os << "Invalid";
                break;
        }

        return os;
    }

    istream& operator>>(istream& is, Location& tmp_location) { return tmp_location.read(is); }
    ostream& operator<<(ostream& os, const Location& tmp_location)
    {
        return tmp_location.display(os);
    }
}  // namespace nure
