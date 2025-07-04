// Order.cpp
// Order class implementation

#include "Order.hpp"
#include <algorithm>
#include <cassert>
#include <chrono>

Order::Order(float _price, int _volume, Trader &_maker)
    : price{_price}, volume{_volume}, maker{&_maker},
      timestamp{std::chrono::steady_clock::now()} {}

Order::Order(const Order &other)
    : price{other.price}, volume{other.volume}, maker{other.maker},
      timestamp{std::chrono::steady_clock::now()} {}

float Order::get_price() const noexcept { return price; }

int Order::get_volume() const noexcept { return volume; }

Trader &Order::get_maker() const noexcept { return *maker; }

int Order::make_trade(const int req_vol) {
  if (req_vol < 0) {
    // taker wants to sell (maker buying)
    return buy_trade(req_vol);
  } else if (req_vol > 0) {
    // taker wants to buy (maker selling)
    return sell_trade(req_vol);
  }

  return 0;
}

int Order::sell_trade(const int req_vol) {
  // maker sell, taker buy
  // req_vol > 0
  assert(volume <= 0);
  int avail = std::min(-volume, req_vol);
  volume += avail;
  return avail;
}

int Order::buy_trade(const int req_vol) {
  // maker buy, taker sell
  // req_vol < 0
  assert(volume >= 0);
  int avail = std::max(-volume, req_vol);
  volume += avail;
  return avail;
}

bool Order::operator<(const Order &other) const noexcept {
  if (this == &other) { return false; }
  
  if (price < other.price) {
    return true;
  }
  if (timestamp < other.timestamp) {
    return true;
  }
  return false;
}

bool Order::operator>(const Order &other) const noexcept {
  if (this == &other) { return false; }
  
  if (price > other.price) {
    return true;
  }
  if (timestamp > other.timestamp) {
    return true;
  }
  return false;
}

bool Order::operator==(const Order &other) const noexcept {
  if (this == &other) { return true; }
  
  if (price == other.price && timestamp == other.timestamp) {
    return true;
  }
  return false;
}