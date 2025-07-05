// Trade.hpp
#pragma once
#include "Trader.hpp"
#include "MarketUtils.hpp"

/**
 * @brief Executed trade
 * 
 */
struct Trade {
  Trade() = delete;
  ~Trade() = default;

  Trade(const Trader *_maker, const Trader *_taker, float _price);
  Trade(Trader &_maker, Trader &_taker, float _price);
  Trade(const Trade &other);
  Trade &operator=(const Trade &) = delete;

  const Trader* const maker;
  const Trader* const taker;
  const float price;
  const MarketUtils::Timestamp timestamp;
};