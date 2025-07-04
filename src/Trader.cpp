// Trader.cpp
#include "Trader.hpp"
#include <string>

Trader::Trader(const Trader &other) : name{other.name} {}

Trader::Trader(const std::string &_name) : name{_name} {}

Trader &Trader::operator=(const Trader &rhs) {
  if (this == &rhs) { return *this; }
  name = rhs.name;
  return *this;
}