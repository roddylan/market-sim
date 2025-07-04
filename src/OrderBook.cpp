// OrderBook.cpp
// OrderBook implementation

#include "OrderBook.hpp"
#include "Order.hpp"
OrderBook::OrderBook(const std::vector<Order> &_buys,
                     const std::vector<Order> &_sells)
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