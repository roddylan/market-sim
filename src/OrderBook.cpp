// OrderBook.cpp
// OrderBook implementation

#include "OrderBook.hpp"
#include "Order.hpp"
OrderBook::OrderBook(const std::vector<Order> &_buys,
                     const std::vector<Order> &_sells)
    : buy_orders(_buys), sell_orders(_sells) {}

OrderBook::OrderBook(const OrderBook &other)
    : buy_orders(other.buy_orders), sell_orders(other.sell_orders) {}