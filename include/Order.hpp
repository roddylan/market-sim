// Order.hpp
// Order object
#ifndef _ORDER_HPP
#define _ORDER_HPP
#include "Trader.hpp"
#include <memory>

/**
 * @class Order
 * @brief Represents Order
 * 
 * Class stores order information, negative volume for short/sell and positive volume for long/buy
 */
class Order { 
public:
  Order() = default;
  ~Order() = default;
  Order(float _price, int _volume) : price{_price}, volume{_volume} {}

  Order(const Order &);
  Order &operator=(const Order &);
  

private:
  float price;
  int volume;
};
















#endif