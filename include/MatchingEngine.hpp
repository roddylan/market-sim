// MatchingEngine.cpp
// Matching and Trade execution
#pragma once

// forward declare Order
class Order;

/**
 * @brief Matching execution logic
 * 
 */
namespace MatchingEngine {

  /**
   * @brief Execute order (partially or fully)
   *
   * @param maker_order maker order
   * @param taker_order taker order
   * @return int volume traded
   */
  int match_order(Order &maker_order, Order &taker_order);

  /**
   * @brief Execute sell order (maker selling, taker buying)
   *
   * @param maker_order
   * @param taker_order
   * @return int volume traded
   */
  int sell_order(Order &maker_order, Order &taker_order);

  /**
   * @brief Execute buy order (maker buying, taker selling)
   *
   * @param maker_order
   * @param taker_order
   * @return int volume traded
   */
  int buy_order(Order &maker_order, Order &taker_order);
};