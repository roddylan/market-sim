// MarketData.hpp
// Market state info and other data
#pragma once
#include "Order.hpp"
#include "Trade.hpp"
#include <memory>
#include <vector>

class MarketData {
public:
  MarketData() = default;
  ~MarketData() = default;
  
  Trade *get_last_trade();
  float get_last_price();
private:
  // stack containing trade history
  std::vector<std::unique_ptr<Trade>> trade_history;
  std::vector<float> price_history;
};