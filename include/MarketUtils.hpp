// Utils.hpp
#pragma once
#include <chrono>

/**
 * @brief Useful types aliases for Market-related functions
 * 
 */
namespace MarketUtils {
  using Timestamp = std::chrono::time_point<std::chrono::steady_clock>;
  using Duration = std::chrono::nanoseconds;
  using Clock = std::chrono::steady_clock;
  using Time = std::chrono::time_point<std::chrono::steady_clock>;
}