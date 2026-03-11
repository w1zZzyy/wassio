#pragma once

#include <coroutine>

namespace wassio::context {

//::::::::::::::::::DECLARATION::::::::::::::::::

template<typename Executor, typename Scheduler>
class Context {
public:
    // coroutine is ready for execution
    void Post(std::coroutine_handle<> h);

    // start handling tasks
    void Run();

private:
    Executor executor_;
    Scheduler scheduler_;

};

//::::::::::::::::::REALIZATION::::::::::::::::::

template<typename E, typename S>
void Context<E, S>::Post(std::coroutine_handle<> h) { 
    scheduler_.Post(h); 
}

template<typename E, typename S>
void Context<E, S>::Run() { 
    for(;;) {
        auto h = scheduler_.Pop();
        if(!h) break;

        executor_.Post(h.value());
    }
}

}