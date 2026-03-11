#pragma once

#include <cstddef>
#include <cstdlib>

namespace wassio::coro {

struct HeapAllocator {
    void* operator new (size_t bytes) {
        return malloc(bytes);
    }
    
    void operator delete (void* ptr) {
        free(ptr);
    }
};

}