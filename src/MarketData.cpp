// MarketData.cpp
#include "MarketData.hpp"
#include "Trade.hpp"
#include <memory>

Trade *MarketData::get_last_trade() const {
  if (trade_history.empty()) {
    return nullptr;
  }
  return trade_history.back().get();
}

float MarketData::get_last_price() const {
  if (price_history.empty()) {
    return 0;
  }
  return price_history.back();
}

const MarketData::Trades &MarketData::get_trade_history() const {
  return trade_history;
}

const std::vector<float> &MarketData::get_prices() const {
  return price_history;
}

void MarketData::add_trade(Trader &maker, Trader &taker, float vwap) {
  trade_history.push_back(std::make_unique<Trade>(maker, taker, vwap));
  price_history.push_back(vwap);
}