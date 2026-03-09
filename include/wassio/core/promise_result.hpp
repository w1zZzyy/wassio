#pragma once

#include <stdexcept>
#include <optional>

namespace wassio::core {

template<typename ReturnType>
class PromiseResult {
public:
    void return_value(ReturnType res) {
        result_ = std::move(res);
    }

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
    void GetResult() {}
};

}