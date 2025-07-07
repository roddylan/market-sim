// Exchange.cpp
#include "Exchange.hpp"
#include "MarketData.hpp"
#include "OrderBook.hpp"
#include <memory>

Exchange::Exchange(float _starting_price)
    : book(std::make_unique<OrderBook>()),
      market_data(std::make_unique<MarketData>()),
      starting_price(_starting_price) {}