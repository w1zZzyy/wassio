#pragma once

#include <coroutine>
#include <optional>
#include <queue>

namespace wassio::context::scheduler {

//::::::::::::::::::DECLARATION::::::::::::::::::

class SingleThreadedScheduler {
public:
    void Post(std::coroutine_handle<>);
    std::optional<std::coroutine_handle<>> Pop() noexcept;

private:
    std::queue<std::coroutine_handle<>> ready_;
};

//::::::::::::::::::REALIZATION::::::::::::::::::

inline void SingleThreadedScheduler::Post(std::coroutine_handle<> h) {
    ready_.push(h);
}

inline std::optional<std::coroutine_handle<>> SingleThreadedScheduler::Pop() noexcept {
    if(ready_.empty()) return std::nullopt;
    auto res = std::move(ready_.front());
    ready_.pop();
    return res;
}

}