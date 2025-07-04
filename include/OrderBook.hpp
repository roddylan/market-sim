// OrderBook.hpp
#pragma once

#include "Order.hpp"
#include <vector>
#include <queue>
#include "OrderUtils.hpp"
#include <memory>

class OrderBook {
public:
  using BuyQueue = std::priority_queue<std::shared_ptr<Order>, std::vector<std::shared_ptr<Order>>, OrderUtils::BuyOrderCompare>;
  using SellQueue = std::priority_queue<std::shared_ptr<Order>, std::vector<std::shared_ptr<Order>>, OrderUtils::SellOrderCompare>;
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
   * @param taker_order 
   * @return float execution price (or average if multiple orders)
   */
  float match(Order &taker_order);
  float sell_match(Order &taker_order);
  float buy_match(Order &taker_order);

private:
  BuyQueue buy_orders;
  SellQueue sell_orders;
};
