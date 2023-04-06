#ifndef NURE_GRID_H
#define NURE_GRID_H

#include <iostream>
#include <iomanip>
#include <queue>
#include <cmath>
#include <cstdlib>

#include "Ship.h"
#include "Error.h"

#define MAP_WIDTH 10
#define MAP_HEIGHT 10

#define ANSI_COLOR_RESET "\033[0m"
#define ANSI_COLOR_WHITE "\033[1;37m"
#define ANSI_COLOR_GREEN "\033[0;32m"
#define ANSI_COLOR_RED "\033[0;31m"
#define ANSI_COLOR_PURPLE "\033[0;35m"
#define ANSI_COLOR_BLUE "\033[0;34m"

namespace nure {
    const char INVALID_COORDINATES[] = "[ERROR] Invalid coordinates";
    const char INVALID_DISTANCE[] = "[ERROR] Minimum distance between ships should be 1";
    const char INVALID_LOCATION[] = "[ERROR] Invalid ship location";
    const char INVALID_DIRECTION[] = "[ERROR] Invalid ship direction";

    enum State { Occupied, Hit, Miss, Dead, Empty };

    class Grid
    {
        std::vector<Ship> ships;

    protected:
        State grid[MAP_HEIGHT][MAP_WIDTH];

        Error error;

        Grid& setEmpty();

        bool areValidNeighbours(Location tmp_location) const;
        bool isValidPosition(Ship& ship);

        bool areValidPossibleNeighbours(Location tmp_location) const;
        bool isValidPossibility(Ship& ship);

        Grid& sunk(Location tmp_location);

    public:
        Grid();
        Grid& generateRandomMap();

        Location calculateHitLocation();

        bool addShip(Ship& ship);
        Grid& hit(Location tmp_location);
        bool isGameOver() const;

        const State& getState(Location location) const;
        const Error& getError() const;
    };

}  // namespace nure

#endif
