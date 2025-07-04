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