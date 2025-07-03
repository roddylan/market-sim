// OrderBook.hpp
#ifndef _ORDER_BOOK_HPP
#define _ORDER_BOOK_HPP
#include <vector>
#include "Order.hpp"
struct OrderBook {
  std::vector<Order> buy_orders;
  std::vector<Order> sell_orders;
};



#endif