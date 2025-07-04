// OrderBook.cpp
// OrderBook implementation

#include "OrderBook.hpp"
#include "MatchingEngine.hpp"
#include <memory>

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

const OrderBook::BuyQueue &OrderBook::get_buy_orders() const {
  return buy_orders;
}

const OrderBook::SellQueue &OrderBook::get_sell_orders() const {
  return sell_orders;
}

bool OrderBook::insert(const Order &order) {
  if (order.get_volume() == 0) {
    return false;
  }

  if (order.get_volume() < 0) {
    // sell order
    sell_orders.push(std::make_shared<Order>(order));
  } else if (order.get_volume() > 0) {
    // buy order
    buy_orders.push(std::make_shared<Order>(order));
  }
  return true;
}

float OrderBook::match(Order &taker_order) {
  const int taker_vol{taker_order.get_volume()};
  if (taker_vol == 0) {
    return 0;
  }
  if (taker_vol < 0) {
    return sell_match(taker_order);
  } else {
    return buy_match(taker_order);
  }
}

float OrderBook::buy_match(Order &taker_order) {
  // match buy order to request
  // (maker buying, taker selling)
  if (buy_orders.empty()) {
    return 0;
  }

  const float fair_price = taker_order.get_price();
  float res{};

  while (taker_order.get_volume() < 0 && !buy_orders.empty()) {
    // todo: dont pop, access order directly since only volume updating
    float book_price = buy_orders.top()->get_price();
    if (fair_price > book_price) {
      // taker wont want to sell, too low
      return res;
    } else {
      res = book_price;
    }

    auto best_order = buy_orders.top();
    buy_orders.pop();
    MatchingEngine::match_order(*best_order, taker_order);
    if (best_order->get_volume() != 0) {
      buy_orders.push(best_order);
    }
  }

  return res;
}

float OrderBook::sell_match(Order &taker_order) {
  // match sell order to request
  // (maker selling, taker buying)
  if (sell_orders.empty()) {
    return 0;
  }
  const float fair_price = taker_order.get_price();
  float res{};

  while (taker_order.get_volume() > 0) {
    // todo: dont pop, access order directly since only volume updating
    float book_price = sell_orders.top()->get_price();
    if (fair_price < book_price) {
      // taker wont want to sell, too high
      return res;
    } else {
      res = book_price;
    }

    auto best_order = sell_orders.top();
    sell_orders.pop();
    MatchingEngine::match_order(*best_order, taker_order);
    if (best_order->get_volume() != 0) {
      sell_orders.push(best_order);
    }
  }

  return res;
}