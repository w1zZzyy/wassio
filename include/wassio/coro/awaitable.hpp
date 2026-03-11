#pragma once

#include <coroutine>

namespace wassio::coro {

template<typename Promise>
class AwaitableNone {
public:
    explicit AwaitableNone(auto) noexcept {} 
    void UpdateHandler(auto) noexcept {}
};

// used only with FinalSuspendAwakeContinuation (FSAC) as FinalSuspendPolicy
// otherwise code wont compile
template<typename Promise>
class Awaitable {
public:
    using handler = std::coroutine_handle<Promise>;

    explicit Awaitable(handler h) noexcept : coro_(h) {}
    void UpdateHandler(handler h) noexcept { coro_ = h; }

    auto operator co_await () noexcept {
        struct Awaiter {
            Awaitable* self;

            bool await_ready() const noexcept { return false; }

            std::coroutine_handle<> await_suspend(std::coroutine_handle<> caller) noexcept {
                auto coro = self->coro_;

                // method from suspend.hpp -> FSAC
                coro.promise().UpdateContinuation(caller);

                return coro;
            }

            auto await_resume() noexcept {
                auto& p = self->coro_.promise();
                
                // methods from exception.hpp
                if(p.HasError()) 
                    p.RethrowException();

                // method from promise_result.hpp
                return p.GetResult();
            }            
        };
        return Awaiter(this);
    }

private:
    handler coro_;

};

}