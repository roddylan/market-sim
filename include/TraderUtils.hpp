// TraderUtils.hpp
// utils for trader
#pragma once
#include "Trader.hpp"
#include <functional>
#include <string>

/**
 * @brief Hash function for Trader
 * 
 */
struct TraderHash {
  inline static const std::hash<std::string> hasher;
  
  size_t operator()(const Trader &trader) const {
    return hasher(trader.get_name());
  }
};