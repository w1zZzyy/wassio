#pragma once

#include "wassio/core/coroutine.hpp"
#include "wassio/core/awaitable.hpp"
#include "wassio/core/exception.hpp"
#include "wassio/core/promise.hpp"
#include "wassio/core/promise_result.hpp"
#include "wassio/core/suspend.hpp"
#include "wassio/core/transform_awaiter.hpp"
#include "wassio/core/promise_storage.hpp"
#include "wassio/core/heap_allocator.hpp"

namespace wassio {

template<typename ResultType>
using AwaitableCoro = 
    core::Coroutine<
        core::Awaitable,
        core::PromiseConfig<
            core::PromiseResult<ResultType>, 
            core::LazySuspend, 
            core::FinalSuspendAwakeContinuation, 
            core::SaveException, 
            core::TransformAwaiterNone,
            core::PromiseStorage<>, 
            core::HeapAllocator>>;

}