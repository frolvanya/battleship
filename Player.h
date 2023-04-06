#ifndef NURE_PLAYER_H
#define NURE_PLAYER_H

#include "Grid.h"

namespace nure {
    class Player
    {
    protected:
        Grid grid;

    public:
        virtual bool is_lost() const;
        virtual Error getError() const;

        virtual State hit() = 0;
        virtual std::ostream& display(std::ostream& os) const = 0;
    };

    class UserPlayer : public Player
    {
    public:
        UserPlayer();

        State hit() override;
        std::ostream& display(std::ostream& os) const override;
    };

    class ComputerPlayer : public Player
    {
    public:
        ComputerPlayer();

        State hit() override;
        std::ostream& display(std::ostream& os) const override;
    };
}  // namespace nure

#endif
