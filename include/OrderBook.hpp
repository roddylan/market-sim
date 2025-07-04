// OrderBook.hpp
#ifndef _ORDER_BOOK_HPP
#define _ORDER_BOOK_HPP
#include "Order.hpp"
#include <vector>
#include <queue>
#include "OrderUtils.hpp"


struct OrderBook {
  using BuyQueue = std::priority_queue<Order, std::vector<Order>, OrderUtils::BuyOrderCompare>;
  using SellQueue = std::priority_queue<Order, std::vector<Order>, OrderUtils::SellOrderCompare>;
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
  OrderBook(const BuyQueue &_buys, const SellQueue &_sells);

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

  /**
   * @brief Insert order into order book
   * 
   * @param order 
   * @return true successfully added
   * @return false failed
   */
  bool insert(const Order &order);

  
  /**
   * @brief Order match logic
   * 
   * @param req_vol 
   * @return float execution price (or average if multiple orders)
   */
  float match(int req_vol);
  float sell_match(int req_vol);
  float buy_match(int req_vol);

  BuyQueue buy_orders;
  SellQueue sell_orders;
};

#endif