#include "gtest/gtest.h"

#include "wassio/context.hpp"
#include "wassio/coro.hpp"

using namespace wassio;

AwaitableCoro<int> task2(SimpleContext* ctx, int& num) {
    num += 1111;
    co_return num;
}

AwaitableCoro<int> task1(SimpleContext* ctx, int& num) {
    co_return num += 22;
}

EntryCoro entry(SimpleContext* ctx) {
    int num = 0;
    co_await task1(ctx, num);
    EXPECT_EQ(num, 22);
    auto res = co_await task2(ctx, num);
    EXPECT_EQ(res, 1133);
}

TEST(WassioCore, Simple) {
    SimpleContext ctx;

    auto coro = entry(&ctx);
    ctx.Post(coro.GetHandler());

    ctx.Run();
}