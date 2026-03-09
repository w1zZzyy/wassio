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

using EntryCoro = 
    core::Coroutine<
        core::Awaitable,
        core::PromiseConfig<
            core::PromiseResult<void>, 
            core::LazySuspend, 
            core::EagerSuspend, 
            core::SaveException, 
            core::TransformAwaiterNone,
            core::PromiseStorage<>, 
            core::HeapAllocator>>;

}