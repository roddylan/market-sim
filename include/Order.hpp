// Order.hpp
// Order object
#ifndef _ORDER_HPP
#define _ORDER_HPP
#include "Trader.hpp"
#include <memory>

class Order { 
public:
  Order();
  ~Order();

  Order(const Order &);
  Order operator=(const Order &);
  

private:
  float price;
  size_t volume;
  std::shared_ptr<Trader> buyer;
  std::shared_ptr<Trader> seller;
};
















#endif