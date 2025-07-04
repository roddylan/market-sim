// MatchingEngine.cpp
// Matching and Trade execution
#pragma once
#include "Order.hpp"

namespace MatchingEngine {

  /**
   * @brief Execute order (partially or fully)
   *
   * @param maker_order maker order
   * @param taker_order taker order
   */
  void match_order(Order &maker_order, Order &taker_order);

  /**
   * @brief Execute sell order (maker selling, taker buying)
   *
   * @param maker_order
   * @param taker_order
   */
  void sell_order(Order &maker_order, Order &taker_order);

  /**
   * @brief Execute buy order (maker buying, taker selling)
   *
   * @param maker_order
   * @param taker_order
   */
  void buy_order(Order &maker_order, Order &taker_order);
};