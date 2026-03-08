#pragma once

#include "wassio/core/promise.hpp"

#include <utility>

namespace wassio::core {
    
/* 
coroutine

- AwaitablePolicy 
    stores coroutine<Promise> continuation if 
    - update_continuation method [required]
    - co_await operator [not required]

- PromiseConfigPolicy
    promise type configuration
*/
template<template <typename> typename AwaitablePolicy, typename PromiseConfigPolicy>
class Coroutine final : public AwaitablePolicy
 <Promise<Coroutine<AwaitablePolicy, PromiseConfigPolicy>, PromiseConfigPolicy>> {
public:
    using promise_type = Promise<Coroutine, PromiseConfigPolicy>;
    using handler = promise_type::handler;
    using awaitable = AwaitablePolicy<promise_type>;

    ~Coroutine() noexcept { destroy(); }

    Coroutine(const Coroutine&) = delete;
    Coroutine& operator=(const Coroutine&) = delete;

    Coroutine(Coroutine&& o) noexcept
        : awaitable(o.handler_)
        , handler_(std::exchange(o.handler_, {}))
    {}

    Coroutine& operator=(Coroutine&& o) noexcept {
        if (this != &o) {
            destroy();
            handler_ = std::exchange(o.handler_, {});
            awaitable::update_continuation(handler_);
        }
        return *this;
    }

private:
    explicit Coroutine(handler h) noexcept : 
        awaitable(h), 
        handler_(h) 
    {}
    void destroy() noexcept { if(handler_) { handler_.destroy(); } }

    friend class Promise<Coroutine, PromiseConfigPolicy>;

    handler handler_;
};

}