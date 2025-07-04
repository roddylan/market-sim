// MatchingEngine.cpp
// Matching and Trade execution
#pragma once
#include "Order.hpp"


class MatchingEngine {
public:
  /**
   * @brief Construct a new Matching Engine object
   * 
   */
  MatchingEngine() = default;
  
  /**
   * @brief Execute order (partially or fully)
   * 
   * @param maker_order maker order
   * @param taker_order taker order
   * @return int volume traded
   */
  int match_order(const Order &maker_order, const Order &taker_order);

private:
  /**
   * @brief Execute sell order (maker selling, taker buying)
   * 
   * @param maker_order 
   * @param taker_order 
   * @return int volume traded
   */
  int sell_order(const Order &maker_order, const Order &taker_order);
  
  /**
   * @brief Execute buy order (maker buying, taker selling)
   * 
   * @param maker_order 
   * @param taker_order 
   * @return int volume traded
   */
  int buy_order(const Order &maker_order, const Order &taker_order);

};