// Utils.hpp
#pragma once
#include <chrono>


namespace MarketUtils {
  using Timestamp = std::chrono::time_point<std::chrono::steady_clock>;
  using Duration = std::chrono::nanoseconds;
  using Clock = std::chrono::steady_clock;
  using Time = std::chrono::time_point<std::chrono::steady_clock>;
}