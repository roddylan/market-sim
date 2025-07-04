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

float OrderBook::match(int req_vol, const float fair_price) {
  if (req_vol == 0) {
    return 0;
  }
  if (req_vol < 0) {
    return sell_match(req_vol, fair_price);
  } else {
    return buy_match(req_vol, fair_price);
  }
}

float OrderBook::buy_match(int req_vol, const float fair_price) {
  // match buy order to request
  // (maker buying, taker selling)
  if (buy_orders.empty()) {
    return 0;
  }
  const float buy_price = buy_orders.top().get_price();
  const float sell_price =
      !sell_orders.empty() ? sell_orders.top().get_price() : buy_price;
  const float base_price = (buy_price + sell_price) / 2;

  while (req_vol < 0) {
    // todo: dont pop, access order directly since only volume updating
    float book_price = buy_orders.top().get_price();
    if (fair_price > book_price) {
      // taker wont want to sell
      return 0;
    }

    auto best_order = buy_orders.top();
    buy_orders.pop();
    req_vol -= best_order.make_trade(req_vol);
    if (best_order.get_volume() != 0) {
      buy_orders.push(best_order);
    }
  }

  return 0;
}

float OrderBook::sell_match(int req_vol, const float fair_price) {
  // match buy order to request
  // (maker buying, taker selling)
  if (sell_orders.empty()) {
    return 0;
  }
  const float sell_price = sell_orders.top().get_price();
  const float buy_price =
      !buy_orders.empty() ? buy_orders.top().get_price() : sell_price;
  const float base_price = (buy_price + sell_price) / 2;

  return 0;
}