#ifndef NURE_ENEMY_GRID_H
#define NURE_ENEMY_GRID_H

#include "Grid.h"

namespace nure {
    class EnemyGrid : public Grid
    {
    public:
        EnemyGrid();

        std::ostream& display(std::ostream& os) const override;
    };

    std::ostream& operator<<(std::ostream& os, const EnemyGrid& rhs);
}  // namespace nure

#endif
