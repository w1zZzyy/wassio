#pragma once

#include <exception>

namespace wassio::core {

class TerminateOnException {
public: 
    void unhandled_exception() { std::terminate(); } 
    bool HasError() const noexcept { return false; }
    void RethrowException() noexcept {}
};

class SaveException {
public:
    void unhandled_exception() noexcept {
        exception = std::current_exception();
    }

    bool HasError() const noexcept {
        if(exception) 
            return true;
        return false;
    }

    void RethrowException() {
        std::rethrow_exception(exception);
    }

private:
    std::exception_ptr exception;

};

}