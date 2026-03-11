#pragma once

#include "wassio/context.hpp"

namespace wassio::coro {

/* 
promise storage
store and manage one of contexts
*/
class PromiseStorage {
public:
    template<typename... Args>
    explicit PromiseStorage(Args&&... args) {
        (try_switch(std::forward<Args>(args)), ...);
    }

    template<typename... Args>
    void PostTask(Args&&... args) {
        std::visit(
            [&args...](auto&& obj) {
                obj->Post(std::forward<Args>(args)...);
            },
            context_
        );
    }

    template<typename Context>
    void SwitchContext(Context* ctx) noexcept {
        static_assert((std::is_constructible_v<OneOfContexts, Context*>));
        context_ = ctx;
    }

private:
    template<typename T>
    void try_switch(T&& arg) {
        if constexpr (std::is_pointer_v<std::decay_t<T>>) {
            SwitchContext(arg);
        }
    }

private:
    OneOfContexts context_;
    
};

}