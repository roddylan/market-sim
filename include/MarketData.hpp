// MarketData.hpp
// Market state info and other data
#pragma once
#include "Trade.hpp"
#include <memory>
#include <vector>

class MarketData {
public:
  using Trades = std::vector<std::unique_ptr<Trade>>;

  MarketData() = default;
  ~MarketData() = default;

  /**
   * @brief Get the last trade (most recent)
   *
   * @return Trade*
   */
  Trade *get_last_trade() const;

  /**
   * @brief Get the last price
   *
   * @return float
   */
  float get_last_price() const;

  /**
   * @brief Get the trade history object
   *
   * @return std::vector<std::unique_ptr<Trade>>
   */
  const Trades &get_trade_history() const;

  /**
   * @brief Get the prices object
   * 
   * @return const std::vector<float>& 
   */
  const std::vector<float> &get_prices() const;

  /**
   * @brief add trade to history (and update price history)
   *
   * @param maker
   * @param taker
   * @param vwap volume weighted average price
   */
  void add_trade(Trader &maker, Trader &taker, float vwap);

private:
  // stack containing trade history
  Trades trade_history;
  std::vector<float> price_history;
};