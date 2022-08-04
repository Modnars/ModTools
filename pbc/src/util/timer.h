/*
 * @Author: modnarshen
 * @Date: 2022/05/17 16:10:18
 * @LastEditors: modnarshen
 * @Description:
 */
#pragma once

#include <chrono>

namespace pbc {

// 关于时间的一些定义
namespace time {
using seconds      = std::chrono::duration<double>;
using milliseconds = std::chrono::duration<double, std::milli>;
using microseconds = std::chrono::duration<double, std::micro>;
using nanoseconds  = std::chrono::duration<double, std::nano>;
} // namespace time

// 计时器
class Timer {
public:
    using timer_clock = std::chrono::system_clock;

public:
    // 开始计时
    void begin() {
        begin_point_ = timer_clock::now();
        end_point_   = TIME_POINT_NONE;
    }

    // 计时结束
    void end() { end_point_ = timer_clock::now(); }

    // 计时时长
    template <typename DURA_TYPE>
    DURA_TYPE use_time() const {
        if (end_point_ == TIME_POINT_NONE)
            return std::chrono::duration_cast<DURA_TYPE>(timer_clock::now() - begin_point_);
        return std::chrono::duration_cast<DURA_TYPE>(end_point_ - begin_point_);
    }

private:
    timer_clock::time_point begin_point_;
    timer_clock::time_point end_point_;
    static const timer_clock::time_point TIME_POINT_NONE;
};

} // namespace pbc
