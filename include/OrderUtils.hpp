// utils.hpp
#ifndef _ORDER_UTILS_HPP
#define _ORDER_UTILS_HPP
#include "Order.hpp"
namespace OrderUtils {
/**
 * @brief Comparator for Buy Orders
 *
 */
struct BuyOrderCompare {
  bool operator()(const Order &left, const Order &right) {
    float l_price{left.get_price()}, r_price{right.get_price()};
    // best price, highest bid
    if (l_price > r_price) {
      return true;
    }
    auto l_time{left.get_time()}, r_time{right.get_time()};
    // earliest time first
    if (l_time < r_time) {
      return true;
    }
    return false;
  }
};

struct SellOrderCompare {
  bool operator()(const Order &left, const Order &right) {
    float l_price{left.get_price()}, r_price{right.get_price()};
    // best price, lowest ask
    if (l_price < r_price) {
      return true;
    }
    auto l_time{left.get_time()}, r_time{right.get_time()};
    if (l_time < r_time) {
      return true;
    }
    return false;
  }
};

} // namespace OrderUtils

#endif