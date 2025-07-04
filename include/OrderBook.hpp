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

  /**
   * @brief Construct a new Order Book object
   *
   * @param _buys
   * @param _sells
   */
  OrderBook(const std::vector<Order> &_buys = {},
            const std::vector<Order> &_sells = {});

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

  std::vector<Order> buy_orders;
  std::vector<Order> sell_orders;
};

#endif