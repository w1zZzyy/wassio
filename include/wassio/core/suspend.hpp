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
struct FinalSuspendAwakeContinuation {
    std::coroutine_handle<> continuation;

    auto final_suspend() noexcept {
        struct Awaiter {
            FinalSuspendAwakeContinuation* self;

            bool await_ready() const noexcept { 
                return false; 
            }

            std::coroutine_handle<> await_suspend(std::coroutine_handle<>) noexcept {
                auto cont = self->continuation;
                return cont ? cont : std::noop_coroutine();
            }

            void await_resume() noexcept {}
        };

        return Awaiter(this);
    }
};

}