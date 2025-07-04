// OrderBook.hpp
#ifndef _ORDER_BOOK_HPP
#define _ORDER_BOOK_HPP
#include "Order.hpp"
#include <vector>
#include <queue>

struct OrderBook {
  /**
   * @brief Construct a new Order Book object
   *
   */
  OrderBook() = default;

  /**
   * @brief Destroy the Order Book object
   *
   */
  ~OrderBook() = default;

  // TODO: value initializer

  /**
   * @brief Construct a new Order Book object
   *
   * @param other
   */
  OrderBook(const OrderBook &other);

  /**
   * @brief Copy assignment
   *
   * @param other
   * @return OrderBook&
   */
  OrderBook &operator=(const OrderBook &other);

  std::priority_queue<Order> buy_orders;
  std::priority_queue<Order> sell_orders;
};

#endif