#pragma once

#include "wassio/coro/coroutine.hpp"
#include "wassio/coro/awaitable.hpp"
#include "wassio/coro/exception.hpp"
#include "wassio/coro/promise.hpp"
#include "wassio/coro/promise_result.hpp"
#include "wassio/coro/suspend.hpp"
#include "wassio/coro/transform_awaiter.hpp"
#include "wassio/coro/promise_storage.hpp"
#include "wassio/coro/heap_allocator.hpp"

namespace wassio {

using EntryCoro = 
    coro::Coroutine<
        coro::AwaitableNone,
        coro::PromiseConfig<
            coro::PromiseResult<void>, 
            coro::InitialSuspendLazy, 
            coro::FinalSuspendLazy, 
            coro::SaveException, 
            coro::TransformAwaiterNone,
            coro::PromiseStorage, 
            coro::HeapAllocator>>;

template<typename ResultType>
using AwaitableCoro = 
    coro::Coroutine<
        coro::Awaitable,
        coro::PromiseConfig<
            coro::PromiseResult<ResultType>, 
            coro::InitialSuspendLazy, 
            coro::FinalSuspendAwakeContinuation, 
            coro::SaveException, 
            coro::TransformAwaiterNone,
            coro::PromiseStorage, 
            coro::HeapAllocator>>;

}