// OrderBook.cpp
// OrderBook implementation

#include "OrderBook.hpp"

OrderBook::OrderBook(const BuyQueue &_buys, const SellQueue &_sells)
    : buy_orders(_buys), sell_orders(_sells) {}

OrderBook::OrderBook(const OrderBook &other)
    : buy_orders(other.buy_orders), sell_orders(other.sell_orders) {}

OrderBook &OrderBook::operator=(const OrderBook &other) {
  if (this == &other) {
    return *this;
  }
  this->buy_orders = other.buy_orders;
  this->sell_orders = other.sell_orders;
  return *this;
}

bool OrderBook::insert(const Order &order) {
  if (order.get_volume() == 0) {
    return false;
  }

  if (order.get_volume() < 0) {
    // sell order
    sell_orders.push(order);
  } else if (order.get_volume() > 0) {
    // buy order
    buy_orders.push(order);
  }
  return true;
}

float OrderBook::match(int req_vol) {
  if (req_vol == 0) { return -1; }
  if (req_vol < 0) {
    return sell_match(req_vol);
  } else {
    return buy_match(req_vol);
  }
}


float OrderBook::buy_match(int req_vol) {
  // match buy order to request
  // (maker buying, taker selling)
  if (buy_orders.empty()) { return -1; }
  const float buy_price = buy_orders.top().get_price();
  const float sell_price = !sell_orders.empty() ? sell_orders.top().get_price() : buy_price;
  const float base_price = (buy_price + sell_price) / 2;
  
  return -1;
}

float OrderBook::sell_match(int req_vol) {
  // match buy order to request
  // (maker buying, taker selling)
  if (sell_orders.empty()) { return -1; }
  const float sell_price = sell_orders.top().get_price();
  const float buy_price = !buy_orders.empty() ? buy_orders.top().get_price() : sell_price;
  const float base_price = (buy_price + sell_price) / 2;
  
  return -1;
}