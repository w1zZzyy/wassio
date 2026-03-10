#pragma once

#include <coroutine>

namespace wassio::context::executor {

struct ImmediateExecutor {
    void Post(std::coroutine_handle<> handler) const {
        handler.resume();
    }
};

}