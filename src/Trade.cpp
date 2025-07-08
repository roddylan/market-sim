// Trade.cpp
#include "Trade.hpp"
#include "MarketUtils.hpp"
#include <stdexcept>

Trade::Trade(const Trader *_maker, const Trader *_taker, float _price)
    : maker(_maker), taker(_taker), price(_price),
      timestamp(MarketUtils::Clock::now()) {
  if (_price <= 0) {
    throw std::invalid_argument("Price must be > 0");
  }
}

Trade::Trade(Trader &_maker, Trader &_taker, float _price)
    : maker(&_maker), taker(&_taker), price(_price),
      timestamp(MarketUtils::Clock::now()) {
  if (_price <= 0) {
    throw std::invalid_argument("Price must be > 0");
  }
}

Trade::Trade(const Trade &other)
    : maker(other.maker), taker(other.taker), price(other.price),
      timestamp(other.timestamp) {}