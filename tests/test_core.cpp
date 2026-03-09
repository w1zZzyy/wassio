#include "gtest/gtest.h"

#include "wassio/entry_coro.hpp"
#include "wassio/awaitable_coro.hpp"

using namespace wassio;

AwaitableCoro<int> task2(int num) {
    co_return 22 + num;
}

AwaitableCoro<int> task1() {
    auto res = co_await task2(2);
    co_return res;
}

EntryCoro entry() {
    auto res = co_await task1();
    EXPECT_EQ(res, 24);
}

TEST(WassioCore, Simple) {
    entry();
}