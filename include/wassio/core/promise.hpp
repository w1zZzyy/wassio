#pragma once

#include <coroutine>

namespace wassio::core {

/* 
promise config

- PromiseReturnPolicy 
    - provides one of methods:
        1) return_value 
        2) return_void
        returns a value stored in promise
    - GetResult

- InitialSuspendPolicy 
    - initial_suspend
        which determines whether the coroutine will start immediately 
        or wait until the resume() method is called

- FinalSuspendPolicy 
    - final_suspend
        which is called after return_* 
        and manages continuation 
  
- ExceptionPolicy 
    - unhandled_exception
    - HasError 
    - RethrowException

- TransformAwaiter 
    - await_transform
        which may exist or may not exist,
        casts to some Awaiter

- Allocator
    - operators new
        allocating coroutine frame
    - operators delete
        deallocating coroutine frame

- Storage
    - object for data storage (executor, logger, ...)
*/
template<
    typename PromiseReturnPolicy, 
    typename InitialSuspendPolicy, 
    typename FinalSuspendPolicy, 
    typename ExceptionPolicy, 
    typename TransformAwaiter,
    typename Storage,
    typename Allocator>
struct PromiseConfig : 
    public PromiseReturnPolicy, 
    public InitialSuspendPolicy,
    public FinalSuspendPolicy,
    public ExceptionPolicy,
    public TransformAwaiter,
    public Storage,
    public Allocator
{
    using Storage::Storage;
    using InitialSuspendPolicy::initial_suspend;
    using FinalSuspendPolicy::final_suspend;
};

/* 
promise 

- Coroutine 
    the task which has promise_type 
- Config 
    PromiseConfig
*/
template<typename Coroutine, typename Config>
struct Promise final : public Config {
    using Config::Config;
    using handler = std::coroutine_handle<Promise>;

    auto get_return_object() {
        return Coroutine(handler::from_promise(*this));
    }
};

}