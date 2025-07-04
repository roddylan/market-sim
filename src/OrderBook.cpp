// OrderBook.cpp
// OrderBook implementation

#include "OrderBook.hpp"


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