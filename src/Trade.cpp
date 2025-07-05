#include "Trade.hpp"

Trade::Trade(const Trader *_maker, const Trader *_taker, float _price)
    : maker(_maker), taker(_taker), price(_price) {
  assert(_price >= 0);
}

Trade::Trade(const Trade &other)
    : maker(other.maker), taker(other.taker), price(other.price) {}