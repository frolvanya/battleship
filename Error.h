#ifndef NURE_ERROR_H
#define NURE_ERROR_H

#include <iostream>
#include <cstring>

namespace nure {
    class Error
    {
        char* message;

        Error& setEmpty();

    public:
        Error();
        Error(const Error& rhs);
        ~Error();

        Error& operator=(const char* tmp_message);
        operator bool() const;

        Error& clear();

        std::ostream& display(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const Error& rhs);
}  // namespace nure

#endif
