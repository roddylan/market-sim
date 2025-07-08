// MatchingEngine.cpp
#include "MatchingEngine.hpp"
#include "Order.hpp"
#include <algorithm>
#include <cassert>

int MatchingEngine::match_order(Order &maker_order, Order &taker_order) {
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

int MatchingEngine::sell_order(Order &maker_order, Order &taker_order) {
  // maker sell, taker buy
  // taker vol > 0
  const int maker_vol{maker_order.get_volume()},
      taker_vol{taker_order.get_volume()};
  assert(maker_vol <= 0);
  assert(taker_vol >= 0);

  // how much taker can buy (+)
  int order_vol = std::min(-maker_vol, taker_vol);
  // maker vol += avail
  maker_order.update_volume(order_vol);
  // taker vol -= avail
  taker_order.update_volume(-order_vol);

  return order_vol;
}

int MatchingEngine::buy_order(Order &maker_order, Order &taker_order) {
  // maker buy, taker sell
  // taker vol < 0
  const int maker_vol{maker_order.get_volume()},
      taker_vol{taker_order.get_volume()};
  assert(maker_vol >= 0);
  assert(taker_vol <= 0);

  // how much taker can sell (-)
  int order_vol = std::max(-maker_vol, taker_vol);
  // maker vol += avail
  maker_order.update_volume(order_vol);
  // taker vol -= avail
  taker_order.update_volume(-order_vol);

  return order_vol;
}