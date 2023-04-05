#ifndef NURE_SHIP_H
#define NURE_SHIP_H

#include <iostream>

namespace nure {
    enum Direction { Up, Down, Left, Right, Invalid };

    class Location
    {
    public:
        int x;
        int y;

        Location();
        Location(int tmp_x, int tmp_y);

        Location& generateRandomLocation();

        bool isValid(int tmp_x, int tmp_y) const;
        operator bool() const;
        Location& operator=(const Location& tmp_location);

        std::istream& read(std::istream& is);
        std::ostream& display(std::ostream& os) const;
    };

    class Ship
    {
        Location location;
        Direction direction;
        int deck;  // from 1 to 4

        Ship& generateRandomShip();

        bool isValid(Location tmp_location, int tmp_deck) const;
        Ship& setInvalid();

    public:
        Ship(int tmp_deck);
        Ship(Location tmp_location, Direction tmp_direction, int tmp_deck);

        operator bool() const;

        Location getLocation() const;
        Location getEndLocation();
        Direction getDirection() const;
        int getDeck() const;
    };

    std::ostream& operator<<(std::ostream& os, const Direction& rhs);

    std::istream& operator>>(std::istream& is, Location& tmp_location);
    std::ostream& operator<<(std::ostream& os, const Location& tmp_location);
}  // namespace nure

#endif
