// Order.cpp
// Order class implementation

#include "Order.hpp"

Order::Order(float _price, int _volume, const std::shared_ptr<Trader> &_maker)
    : price{_price}, volume{_volume}, maker{_maker} {}

Order::Order(const Order &other)
    : price{other.price}, volume{other.volume}, maker{other.maker} {}

float Order::get_price() const noexcept {
  return price;
}

int Order::get_volume() const noexcept {
  return volume;
}

Trader &Order::get_maker() const noexcept {
  return *maker;
}

