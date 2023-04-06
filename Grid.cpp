#include "Grid.h"

using namespace std;

namespace nure {
    Grid& Grid::setEmpty()
    {
        for (int i = 0; i < MAP_HEIGHT; i++) {
            for (int j = 0; j < MAP_WIDTH; j++) {
                grid[i][j] = State::Empty;
            }
        }

        return *this;
    }

    bool Grid::areValidNeighbours(Location tmp_location) const
    {
        Location neighbours[8] = {
            Location(tmp_location.x - 1, tmp_location.y - 1),
            Location(tmp_location.x - 1, tmp_location.y),
            Location(tmp_location.x - 1, tmp_location.y + 1),
            Location(tmp_location.x, tmp_location.y - 1),
            Location(tmp_location.x, tmp_location.y + 1),
            Location(tmp_location.x + 1, tmp_location.y - 1),
            Location(tmp_location.x + 1, tmp_location.y),
            Location(tmp_location.x + 1, tmp_location.y + 1),
        };

        for (Location neighbour : neighbours) {
            if (neighbour && grid[neighbour.y][neighbour.x] != State::Empty) {
                return false;
            }
        }

        return true;
    }

    bool Grid::isValidPosition(Ship& ship)
    {
        error.clear();

        Location tmp_location = ship.getLocation();
        switch (ship.getDirection()) {
            case Direction::Up:
                for (int y = tmp_location.y; y > tmp_location.y - ship.getDeck(); y--) {
                    if (!Location(tmp_location.x, y) || grid[y][tmp_location.x] != State::Empty ||
                        !areValidNeighbours(Location(tmp_location.x, y))) {
                        error = INVALID_LOCATION;
                        return false;
                    }
                }
                break;
            case Direction::Down:
                for (int y = tmp_location.y; y < tmp_location.y + ship.getDeck(); y++) {
                    if (!Location(tmp_location.x, y) || grid[y][tmp_location.x] != State::Empty ||
                        !areValidNeighbours(Location(tmp_location.x, y))) {
                        error = INVALID_LOCATION;
                        return false;
                    }
                }
                break;
            case Direction::Left:
                for (int x = tmp_location.x; x > tmp_location.x - ship.getDeck(); x--) {
                    if (!Location(x, tmp_location.y) || grid[tmp_location.y][x] != State::Empty ||
                        !areValidNeighbours(Location(x, tmp_location.y))) {
                        error = INVALID_LOCATION;
                        return false;
                    }
                }
                break;
            case Direction::Right:
                for (int x = tmp_location.x; x < tmp_location.x + ship.getDeck(); x++) {
                    if (!Location(x, tmp_location.y) || grid[tmp_location.y][x] != State::Empty ||
                        !areValidNeighbours(Location(x, tmp_location.y))) {
                        error = INVALID_LOCATION;
                        return false;
                    }
                }
                break;
            case Direction::Invalid:
                error = INVALID_DIRECTION;
                return false;
        }

        return true;
    }

    bool Grid::areValidPossibleNeighbours(Location tmp_location) const
    {
        Location neighbours[8] = {
            Location(tmp_location.x - 1, tmp_location.y - 1),
            Location(tmp_location.x - 1, tmp_location.y),
            Location(tmp_location.x - 1, tmp_location.y + 1),
            Location(tmp_location.x, tmp_location.y - 1),
            Location(tmp_location.x, tmp_location.y + 1),
            Location(tmp_location.x + 1, tmp_location.y - 1),
            Location(tmp_location.x + 1, tmp_location.y),
            Location(tmp_location.x + 1, tmp_location.y + 1),
        };

        for (Location neighbour : neighbours) {
            if (neighbour && grid[neighbour.y][neighbour.x] == State::Dead) {
                return false;
            }
        }

        return true;
    }

    bool Grid::isValidPossibility(Ship& ship)
    {
        Location tmp_location = ship.getLocation();
        switch (ship.getDirection()) {
            case Direction::Up:
                for (int y = tmp_location.y; y > tmp_location.y - ship.getDeck(); y--) {
                    if (!Location(tmp_location.x, y) || grid[y][tmp_location.x] == State::Miss ||
                        grid[y][tmp_location.x] == State::Dead ||
                        !areValidPossibleNeighbours(Location(tmp_location.x, y))) {
                        return false;
                    }
                }
                break;
            case Direction::Down:
                for (int y = tmp_location.y; y < tmp_location.y + ship.getDeck(); y++) {
                    if (!Location(tmp_location.x, y) || grid[y][tmp_location.x] == State::Miss ||
                        grid[y][tmp_location.x] == State::Dead ||
                        !areValidPossibleNeighbours(Location(tmp_location.x, y))) {
                        return false;
                    }
                }
                break;
            case Direction::Left:
                for (int x = tmp_location.x; x > tmp_location.x - ship.getDeck(); x--) {
                    if (!Location(x, tmp_location.y) || grid[tmp_location.y][x] == State::Miss ||
                        grid[tmp_location.y][x] == State::Dead ||
                        !areValidPossibleNeighbours(Location(x, tmp_location.y))) {
                        return false;
                    }
                }
                break;
            case Direction::Right:
                for (int x = tmp_location.x; x < tmp_location.x + ship.getDeck(); x++) {
                    if (!Location(x, tmp_location.y) || grid[tmp_location.y][x] == State::Miss ||
                        grid[tmp_location.y][x] == State::Dead ||
                        !areValidPossibleNeighbours(Location(x, tmp_location.y))) {
                        return false;
                    }
                }
                break;
            case Direction::Invalid:
                error = INVALID_DIRECTION;
                return false;
        }

        return true;
    }

    Grid::Grid() { setEmpty(); }

    Grid& Grid::generateRandomMap()
    {
        setEmpty();

        int succeeded_generations = 0;
        int tries = 0;
        while (succeeded_generations < 4) {
            ++tries;

            Ship random_ship(1);

            if (addShip(random_ship)) {
                ++succeeded_generations;
            }
        }

        succeeded_generations = 0;
        while (succeeded_generations < 3) {
            ++tries;
            Ship random_ship(2);

            if (addShip(random_ship)) {
                ++succeeded_generations;
            }
        }

        succeeded_generations = 0;
        while (succeeded_generations < 2) {
            ++tries;
            Ship random_ship(3);

            if (addShip(random_ship)) {
                ++succeeded_generations;
            }

            if (tries > 1000) {
                return generateRandomMap();
            }
        }

        succeeded_generations = 0;
        while (succeeded_generations < 1) {
            ++tries;
            Ship random_ship(4);

            if (addShip(random_ship)) {
                ++succeeded_generations;
            }

            if (tries > 1000) {
                return generateRandomMap();
            }
        }

        return *this;
    }

    bool Grid::addShip(Ship& ship)
    {
        error.clear();

        if (!ship) {
            error = INVALID_LOCATION;
            return false;
        }

        if (!isValidPosition(ship)) {
            return false;
        }

        ships.push_back(ship);

        Location tmp_location = ship.getLocation();
        switch (ship.getDirection()) {
            case Direction::Up:
                for (int y = tmp_location.y; y > tmp_location.y - ship.getDeck(); y--) {
                    grid[y][tmp_location.x] = State::Occupied;
                }
                break;
            case Direction::Down:
                for (int y = tmp_location.y; y < tmp_location.y + ship.getDeck(); y++) {
                    grid[y][tmp_location.x] = State::Occupied;
                }
                break;
            case Direction::Left:
                for (int x = tmp_location.x; x > tmp_location.x - ship.getDeck(); x--) {
                    grid[tmp_location.y][x] = State::Occupied;
                }
                break;
            case Direction::Right:
                for (int x = tmp_location.x; x < tmp_location.x + ship.getDeck(); x++) {
                    grid[tmp_location.y][x] = State::Occupied;
                }
                break;
            case Direction::Invalid:
                error = INVALID_DIRECTION;
                return false;
        }

        return true;
    }

    Grid& Grid::sunk(Location tmp_location)
    {
        if (tmp_location && grid[tmp_location.y][tmp_location.x] == State::Empty) {
            grid[tmp_location.y][tmp_location.x] = State::Miss;
        }

        if (!tmp_location || grid[tmp_location.y][tmp_location.x] != State::Hit) {
            return *this;
        }

        grid[tmp_location.y][tmp_location.x] = State::Dead;

        sunk(Location(tmp_location.x - 1, tmp_location.y));
        sunk(Location(tmp_location.x + 1, tmp_location.y));
        sunk(Location(tmp_location.x, tmp_location.y - 1));
        sunk(Location(tmp_location.x, tmp_location.y + 1));

        sunk(Location(tmp_location.x - 1, tmp_location.y - 1));
        sunk(Location(tmp_location.x - 1, tmp_location.y + 1));
        sunk(Location(tmp_location.x + 1, tmp_location.y - 1));
        sunk(Location(tmp_location.x + 1, tmp_location.y + 1));

        return *this;
    }

    Location Grid::calculateHitLocation()
    {
        int probability[MAP_HEIGHT][MAP_WIDTH]{};
        int max_probability = 0;

        int decks[] = {0, 0, 0, 0};

        for (Ship ship : ships) {
            decks[ship.getDeck() - 1] = 1;
        }

        for (int i = 0; i < MAP_HEIGHT; i++) {
            for (int j = 0; j < MAP_WIDTH; j++) {
                probability[i][j] = 0;

                if (grid[i][j] == State::Empty || grid[i][j] == State::Occupied) {
                    probability[i][j] = 10;

                    for (int deck = 2; deck <= 4; deck++) {
                        if (!decks[deck - 1]) {
                            continue;
                        }

                        Ship possibleShips[] = {Ship(Location(j, i), Direction::Up, deck),
                                                Ship(Location(j, i), Direction::Down, deck),
                                                Ship(Location(j, i), Direction::Left, deck),
                                                Ship(Location(j, i), Direction::Right, deck)};

                        for (Ship ship : possibleShips) {
                            if (isValidPossibility(ship)) {
                                probability[i][j] += deck * 10;

                                Location neighbours[4] = {
                                    Location(j - 1, i),
                                    Location(j + 1, i),
                                    Location(j, i - 1),
                                    Location(j, i + 1),
                                };

                                for (Location neighbour : neighbours) {
                                    if (neighbour && grid[neighbour.y][neighbour.x] == State::Hit) {
                                        probability[i][j] += 1000;
                                    }
                                }
                            }
                        }
                    }
                }

                if (probability[i][j] > max_probability) {
                    max_probability = probability[i][j];
                }
            }
        }

        vector<Location> max_probability_locations;
        for (int i = 0; i < MAP_HEIGHT; i++) {
            for (int j = 0; j < MAP_WIDTH; j++) {
                if (probability[i][j] == max_probability) {
                    max_probability_locations.push_back(Location(j, i));
                }
            }
        }

        return max_probability_locations[std::rand() % max_probability_locations.size()];
    }

    Grid& Grid::hit(Location tmp_location)
    {
        if (tmp_location) {
            int ship_index = -1;
            bool is_sunk = true;

            switch (grid[tmp_location.y][tmp_location.x]) {
                case State::Empty:
                    grid[tmp_location.y][tmp_location.x] = State::Miss;
                    break;
                case State::Occupied:
                    grid[tmp_location.y][tmp_location.x] = State::Hit;

                    for (int i = 0; i < ships.size(); i++) {
                        Location ship_start_location = ships[i].getLocation();
                        Location ship_end_location = ships[i].getEndLocation();

                        if (tmp_location.x >= ship_start_location.x &&
                            tmp_location.x <= ship_end_location.x &&
                            tmp_location.y >= ship_start_location.y &&
                            tmp_location.y <= ship_end_location.y) {
                            ship_index = i;
                            break;
                        }
                    }

                    if (ship_index > -1) {
                        for (int y = ships[ship_index].getLocation().y;
                             y <= ships[ship_index].getEndLocation().y; y++) {
                            for (int x = ships[ship_index].getLocation().x;
                                 x <= ships[ship_index].getEndLocation().x; x++) {
                                if (grid[y][x] == State::Occupied) {
                                    is_sunk = false;
                                }
                            }
                        }

                        if (is_sunk) {
                            sunk(tmp_location);
                            ships.erase(ships.begin() + ship_index);
                        }
                    }

                    break;
                default:
                    error = INVALID_LOCATION;
                    break;
            }
        }

        return *this;
    }

    bool Grid::isGameOver() const { return ships.size() == 0; }

    const State& Grid::getState(Location location) const { return grid[location.y][location.x]; }
    const Error& Grid::getError() const { return error; }

}  // namespace nure
