// MarketData.hpp
// Market state info and other data
#pragma once
#include "Order.hpp"

/**
 * @brief Current market data
 * 
 */
struct MarketData {
  MarketData() = default;
  ~MarketData() = default;
  MarketData(float _price);


  float price;
  float market_price;
  Order::Timestamp timestamp;


};