// Order.cpp
// Order class implementation

#include "Order.hpp"

Order::Order(float _price, int _volume, const std::shared_ptr<Trader> &_maker)
    : price{_price}, volume{_volume}, maker{_maker} {}