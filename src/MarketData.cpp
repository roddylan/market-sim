// MarketData.cpp
#include "MarketData.hpp"
#include "Trade.hpp"
#include <memory>

Trade *MarketData::get_last_trade() {
  return trade_history.back().get();
}

float MarketData::get_last_price() {
  return price_history.back();
}


void MarketData::add_trade(Trader &maker, Trader &taker, float vwap) {
  trade_history.push_back(
    std::make_unique<Trade>(maker, taker, vwap)
  );
  price_history.push_back(vwap);
}