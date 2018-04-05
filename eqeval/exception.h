#ifndef EQEVAL_EXCEPTION_H
#define EQEVAL_EXCEPTION_H

#include <exception>
#include <string>

namespace eqeval {

struct Exception : public std::exception {
    Exception()
        : reason_("") {}
    Exception(const std::string &reason, bool recoverable = false)
        : reason_(reason), recoverable_(recoverable) {}
    const char *what() const throw() { return reason_.c_str(); };
    bool isRecoverable() const { return recoverable_; };

  private:
    const std::string reason_;
    bool recoverable_;
};

} // namespace eqeval

#endif // EQEVAL_EXCEPTION_H