// Order.cpp
// Order class implementation

#include "Order.hpp"
#include <chrono>

Order::Order(float _price, int _volume, Trader &_maker)
    : price{_price}, volume{_volume}, maker{&_maker}, timestamp{std::chrono::steady_clock::now()} {}

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

