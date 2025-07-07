// MarketData.cpp
#include "MarketData.hpp"

Trade *MarketData::get_last_trade() {
  return trade_history.back().get();
}

float MarketData::get_last_price() {
  return price_history.back();
}