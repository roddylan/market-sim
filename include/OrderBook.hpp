// OrderBook.hpp
#ifndef _ORDER_BOOK_HPP
#define _ORDER_BOOK_HPP
#include "Order.hpp"
#include <vector>

struct OrderBook {
  // default/empty constructor
  OrderBook() = default;
  // destructor
  ~OrderBook();
  // value constructor
  OrderBook(const std::vector<Order> &_buys = {},
            const std::vector<Order> &_sells = {})
      : buy_orders(_buys), sell_orders(_sells) {}
  // copy constructor
  OrderBook(const OrderBook &);
  // copy assignment
  OrderBook &operator=(const OrderBook &);

  std::vector<Order> buy_orders;
  std::vector<Order> sell_orders;
};

#endif