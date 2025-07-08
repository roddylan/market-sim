// Trade.cpp
#include "Trade.hpp"
#include "MarketUtils.hpp"
#include <cassert>


Trade::Trade(const Trader *_maker, const Trader *_taker, float _price)
    : maker(_maker), taker(_taker), price(_price), timestamp(MarketUtils::Clock::now()) {
  assert(_price > 0);
}

Trade::Trade(Trader &_maker, Trader &_taker, float _price)
    : maker(&_maker), taker(&_taker), price(_price), timestamp(MarketUtils::Clock::now()) {
  assert(_price > 0);
}

Trade::Trade(const Trade &other)
    : maker(other.maker), taker(other.taker), price(other.price), timestamp(other.timestamp) {}