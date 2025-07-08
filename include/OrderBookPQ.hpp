// OrderBookPQ.hpp
#pragma once

#include "Order.hpp"
#include <vector>
#include <queue>
#include "OrderUtils.hpp"
#include <memory>

/**
 * @class OrderBookPQ
 * @brief (**deprecated**) Order book storing market maker limit orders; handles match and make
 * logic. Uses priority queue.
 *
 * Orders stored in ordered priority queue. Buys sorted by best bid (highest) and
 * earliest time. Sells sorted by best ask (lowest) and earliest time
 */
class OrderBookPQ {
public:
  using BuyQueue = std::priority_queue<std::shared_ptr<Order>, std::vector<std::shared_ptr<Order>>, OrderUtils::BuyOrderComparePQ>;
  using SellQueue = std::priority_queue<std::shared_ptr<Order>, std::vector<std::shared_ptr<Order>>, OrderUtils::SellOrderComparePQ>;
  /**
   * @brief Construct a new Order Book object
   *
   */
  OrderBookPQ() = default;

  /**
   * @brief Destroy the Order Book object
   *
   */
  ~OrderBookPQ() = default;

  /**
   * @brief Construct a new Order Book object
   * 
   * @param _buys 
   * @param _sells 
   */
  OrderBookPQ(const BuyQueue &_buys, const SellQueue &_sells);

  /**
   * @brief Construct a new Order Book object
   *
   * @param other
   */
  OrderBookPQ(const OrderBookPQ &other);

  /**
   * @brief Copy assignment
   *
   * @param other
   * @return OrderBookPQ&
   */
  OrderBookPQ &operator=(const OrderBookPQ &other);

  /**
   * @brief Get the buy orders object
   * 
   * @return const BuyQueue& 
   */
  const BuyQueue &get_buy_orders() const;
  
  /**
   * @brief Get the sell orders object
   * 
   * @return const SellQueue& 
   */
  const SellQueue &get_sell_orders() const;

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
  

private:
  /**
   * @brief Order match logic for sells
   * 
   * @param taker_order 
   * @return float 
   */
  float sell_match(Order &taker_order);
  
  /**
   * @brief Order match logic for buys
   * 
   * @param taker_order 
   * @return float 
   */
  float buy_match(Order &taker_order);
  BuyQueue buy_orders;
  SellQueue sell_orders;
};
