#ifndef EQEVAL_EXCEPTION_H_
#define EQEVAL_EXCEPTION_H_

#include <exception>
#include <string>

namespace eqeval {

/// General purpose wrapper for std::exception to enable a recoverable or non-recoverable flag
/// Use the what() function to get the reason
/// Use isRecoverable() to understand if the exception causes a failure or can be handled in another way
struct Exception : public std::exception {
    Exception()
        : reason_("") {}
    Exception(const std::string &reason, bool recoverable = false)
        : reason_(reason)
        , recoverable_(recoverable) {}
    const char *what() const throw() { return reason_.c_str(); };
    bool isRecoverable() const { return recoverable_; };

  private:
    const std::string reason_;
    bool recoverable_;
};

} // namespace eqeval

#endif // EQEVAL_EXCEPTION_H_