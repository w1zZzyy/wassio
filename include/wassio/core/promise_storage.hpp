#pragma once

#include <tuple>
#include <type_traits>
#include <utility>

namespace wassio::core {

namespace {

template<typename T, typename... TS>
concept is_unique = !(std::is_same_v<T, TS> || ...);

}

template<typename... StorageArgs>
class PromiseStorage {
    static_assert(
        (is_unique<StorageArgs, StorageArgs...> && ...), 
        "args must be unique"
    );
public:
    explicit PromiseStorage(StorageArgs&&... args)
        : args_(std::forward<StorageArgs>(args)...)
    {}

    PromiseStorage() = default;

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
        std::get<T>(args_) = std::forward<T>(v);
    }

private:
    std::tuple<StorageArgs...> args_;
};

}