#include "Error.h"

using namespace std;

namespace nure {
    Error& Error::setEmpty()
    {
        delete[] message;
        message = nullptr;

        return *this;
    }

    Error::Error() : message(nullptr) {}
    Error::Error(const Error& rhs) : message(nullptr)
    {
        if (this != &rhs) {
            operator=(rhs.message);
        }
    }
    Error::~Error() { delete[] message; }

    Error& Error::operator=(const char* tmp_message)
    {
        setEmpty();

        if (tmp_message) {
            message = new char[strlen(tmp_message) + 1];
            strcpy(message, tmp_message);
            message[strlen(tmp_message)] = '\0';
        }

        return *this;
    }
    Error::operator bool() const { return message != nullptr; }

    Error& Error::clear()
    {
        setEmpty();
        return *this;
    }

    ostream& Error::display(ostream& os) const
    {
        if (*this) {
            os << message;
        }
        return os;
    }

    ostream& operator<<(ostream& os, const Error& rhs) { return rhs.display(os); }
}  // namespace nure
