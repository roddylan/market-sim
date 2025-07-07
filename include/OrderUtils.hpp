// utils.hpp
#pragma once
#include "Order.hpp"
#include <memory>
namespace OrderUtils {
  /**
  * @brief Comparator for Buy Orders (priority queue)
  *
  */
  struct BuyOrderCompare {
    bool operator()(const std::shared_ptr<Order> &left, const std::shared_ptr<Order> &right) {
      float l_price{left->get_price()}, r_price{right->get_price()};
      // best price, highest bid
      if (l_price != r_price) {
        return l_price < r_price;
      }
      
      // earliest time first
      return left->get_time() > right->get_time();
    }
  };

  /**
  * @brief Comparator for Sell Orders (priority queue)
  * 
  */
  struct SellOrderCompare {
    bool operator()(const std::shared_ptr<Order> &left, const std::shared_ptr<Order> &right) {
      float l_price{left->get_price()}, r_price{right->get_price()};
      // best price, lowest ask
      if (l_price != r_price) {
        return l_price > r_price;
      }
      
      // earliest time first
      return left->get_time() > right->get_time();
    }
};

} // namespace OrderUtils

