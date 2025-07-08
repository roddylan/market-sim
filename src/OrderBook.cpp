// OrderBook.cpp
// OrderBook implementation

#include "OrderBook.hpp"
#include "MatchingEngine.hpp"
// #include <cassert>
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
    sell_orders.insert(std::make_shared<Order>(order));
  } else if (order.get_volume() > 0) {
    // buy order
    buy_orders.insert(std::make_shared<Order>(order));
  }
  return true;
}

// TODO: return trades instead
float OrderBook::match(Order &taker_order) {
  const int taker_vol{taker_order.get_volume()};
  if (taker_vol == 0) {
    return 0;
  }
  if (taker_vol < 0) {
    return buy_match(taker_order);
  } else {
    return sell_match(taker_order);
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
  size_t total_vol{};

  while (taker_order.get_volume() < 0 && !buy_orders.empty()) {
    // todo: dont pop, access order directly since only volume updating
    float book_price = (*buy_orders.begin())->get_price();
    
    if (fair_price > book_price) {
      // taker wont want to sell, too low
      break;
      // return res;
      // continue;
    } 

    auto best_order = (*buy_orders.begin());
    buy_orders.erase(buy_orders.begin());
    
    int traded_vol = MatchingEngine::match_order(*best_order, taker_order);
    size_t abs_vol = std::abs(traded_vol);
    
    res += book_price * abs_vol;
    total_vol += abs_vol;

    if (best_order->get_volume() != 0) {
      buy_orders.insert(best_order);
    }
  }
  return (total_vol != 0) ? (res / total_vol) : res;
  // return res;
}

float OrderBook::sell_match(Order &taker_order) {
  // match sell order to request
  // (maker selling, taker buying)
  if (sell_orders.empty()) {
    return 0;
  }
  const float fair_price = taker_order.get_price();
  float res{};
  size_t total_vol{};

  while (taker_order.get_volume() > 0 && !sell_orders.empty()) {
    // todo: dont pop, access order directly since only volume updating
    float book_price = (*sell_orders.begin())->get_price();
    if (fair_price < book_price) {
      // taker wont want to buy, too high
      break;
      // return res;
      // continue;
    } 

    auto best_order = *sell_orders.begin();
    sell_orders.erase(sell_orders.begin());
    
    int traded_vol = MatchingEngine::match_order(*best_order, taker_order);
    size_t abs_vol = std::abs(traded_vol);

    res += book_price * abs_vol;
    total_vol += abs_vol;

    if (best_order->get_volume() != 0) {
      sell_orders.insert(best_order);
    }
  }
  return (total_vol != 0) ? (res / total_vol) : res;
}