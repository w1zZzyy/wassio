#pragma once

#include "wassio/context/context.hpp"
#include "wassio/context/executors/immediate_executor.hpp"
#include "wassio/context/schedulers/single_threaded.hpp"

namespace wassio {

using SimpleContext = context::Context<
    context::executor::ImmediateExecutor, 
    context::scheduler::SingleThreadedScheduler>;

}