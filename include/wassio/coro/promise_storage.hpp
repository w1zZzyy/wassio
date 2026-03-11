#pragma once

#include <tuple>
#include <type_traits>
#include <utility>

namespace wassio::coro {

namespace {

template<typename T, typename... TS>
concept is_unique = !(std::is_same_v<T, TS> || ...);

}

/* 
promise storage

- StorageArgs 
    1) args are unique
    2) use it as storage for necessary data (executor, logger, scheduler...)
*/
template<typename... StorageArgs>
class PromiseStorage {
    static_assert(
        (is_unique<StorageArgs, StorageArgs...> && ...), 
        "args must be unique"
    );

    template<typename T>
    void init_if_exists(T&& arg) {
        if constexpr ((std::is_same_v<std::decay_t<T>, StorageArgs> || ...)) {
            SetArg(std::forward<T>(arg));
        }
    }

public:
    template<typename... Args>
    explicit PromiseStorage(Args&&... args) {
        (init_if_exists(std::forward<Args>(args)), ...);
    }

    template<typename T>
    T& GetArg() {
        return std::get<T>(args_);
    }

    template<typename T>
    const T& GetArg() const {
        return std::get<T>(args_);
    }

    template<typename T>
    void SetArg(T&& v) {
        std::get<std::decay_t<T>>(args_) = std::forward<T>(v);
    }

private:
    std::tuple<StorageArgs...> args_;
};

}