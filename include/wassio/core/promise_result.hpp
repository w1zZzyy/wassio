#pragma once

#include <stdexcept>
#include <optional>

namespace wassio::core {

template<typename ReturnType>
class PromiseResult {
    void return_value(ReturnType res) {
        result_ = std::move(res);
    }

    auto& GetOptionalResult() noexcept { return result_; }

    ReturnType& GetResult() {
        if(!result_) throw std::runtime_error("no promise result");
        return result_.value();
    }

private:
    std::optional<ReturnType> result_;
};

template<>
struct PromiseResult<void> {
    void return_void() {}
    void GetOptionalResult() noexcept {}
    void GetResult() {}
};

}