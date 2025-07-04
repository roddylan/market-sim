// utils.hpp
#pragma once
#include "Order.hpp"
#include <memory>
namespace OrderUtils {
/**
 * @brief Comparator for Buy Orders
 *
 */
struct BuyOrderCompare {
  bool operator()(const std::shared_ptr<Order> &left, const std::shared_ptr<Order> &right) {
    float l_price{left->get_price()}, r_price{right->get_price()};
    // best price, highest bid
    if (l_price < r_price) {
      return true;
    }
    
    auto l_time{left->get_time()}, r_time{right->get_time()};
    // earliest time first
    return l_time > r_time;
  }
};

/**
 * @brief Comparator for Sell Orders
 * 
 */
struct SellOrderCompare {
  bool operator()(const std::shared_ptr<Order> &left, const std::shared_ptr<Order> &right) {
    float l_price{left->get_price()}, r_price{right->get_price()};
    // best price, lowest ask
    if (l_price > r_price) {
      return true;
    }
    
    auto l_time{left->get_time()}, r_time{right->get_time()};
    // earliest first
    return l_time > r_time;
  }
};

} // namespace OrderUtils

