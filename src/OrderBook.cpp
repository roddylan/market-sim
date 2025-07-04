// OrderBook.cpp
// OrderBook implementation

#include "OrderBook.hpp"

OrderBook::OrderBook(const std::vector<Order> &_buys,
                     const std::vector<Order> &_sells)
    : buy_orders(_buys), sell_orders(_sells) {}