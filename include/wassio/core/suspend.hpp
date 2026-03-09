#pragma once

#include <coroutine>

namespace wassio::core {

struct LazySuspend { 
    auto initial_suspend() noexcept { return std::suspend_always{}; } 
    auto final_suspend() noexcept { return std::suspend_always{}; } 
};

struct EagerSuspend { 
    auto initial_suspend() noexcept { return std::suspend_never{}; } 
    auto final_suspend() noexcept { return std::suspend_never{}; } 
};

// resumes parent corutine
class FinalSuspendAwakeContinuation {
public:
    void UpdateContinuation(std::coroutine_handle<> caller) noexcept {
        continuation_ = caller;
    }

    auto final_suspend() noexcept {
        struct Awaiter {
            FinalSuspendAwakeContinuation* self;

            bool await_ready() const noexcept { 
                return false; 
            }

            std::coroutine_handle<> await_suspend(std::coroutine_handle<>) noexcept {
                auto cont = self->continuation_;
                return cont ? cont : std::noop_coroutine();
            }

            void await_resume() noexcept {}
        };

        return Awaiter(this);
    }

private:
    std::coroutine_handle<> continuation_;

};

}