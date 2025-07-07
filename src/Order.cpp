// Order.cpp
// Order class implementation

#include "Order.hpp"
#include <algorithm>
#include <cassert>
#include <chrono>

Order::Order(float _price, int _volume, Trader &_trader)
    : volume{_volume}, trader{&_trader}, timestamp{
                                             std::chrono::steady_clock::now()} {
  assert(_price > 0);
  price = _price;
}

Order::Order(float _price, int _volume, const Trader *const _trader)
    : volume{_volume}, trader{_trader}, timestamp{
                                            std::chrono::steady_clock::now()} {
  assert(_price > 0);
  price = _price;
}

Order::Order(float _price, int _volume, Trader &_trader,
             const MarketUtils::Timestamp &_timestamp)
    : volume{_volume}, trader{&_trader}, timestamp{_timestamp} {
  assert(_price > 0);
  price = _price;
}

Order::Order(float _price, int _volume, const Trader *const _trader,
             const MarketUtils::Timestamp &_timestamp)
    : volume{_volume}, trader{_trader}, timestamp{_timestamp} {
  assert(_price > 0);
  price = _price;
}

Order::Order(const Order &other)
    : price{other.price}, volume{other.volume}, trader{other.trader},
      timestamp{other.timestamp} {}

float Order::get_price() const noexcept { return price; }

int Order::get_volume() const noexcept { return volume; }

const Trader &Order::get_trader() const noexcept { return *trader; }

MarketUtils::Timestamp Order::get_time() const noexcept { return timestamp; }

void Order::update_volume(const int &inc) { volume += inc; }

bool Order::operator==(const Order &other) const {
  if (this == &other) {
    return true;
  }

  return (this->price == other.price && this->timestamp == other.timestamp &&
          this->volume == other.volume && this->trader == other.trader);
}