// MatchingEngine.cpp
#include "MatchingEngine.hpp"

int MatchingEngine::match_order(const Order &maker_order, const Order &taker_order) {
  const int requested_vol = taker_order.get_volume();

  if (requested_vol < 0) {
    // taker wants to sell
    // maker buys, taker sells
    return buy_order(maker_order, taker_order);
  }
  if (requested_vol > 0) {
    // taker wants to buy
    // maker sells, taker buys
    return sell_order(maker_order, taker_order);
  }
  return 0;
}


