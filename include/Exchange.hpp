// Exchange.hpp
// Simulate exchange
#pragma once
#include "MarketData.hpp"
#include "OrderBook.hpp"
#include "Trader.hpp"
#include <vector>
#include <memory>

class Exchange {
public:
  Exchange() = delete;
  ~Exchange();

  void run();
private:
  // traders
  std::vector<std::unique_ptr<Trader>> makers;
  std::vector<std::unique_ptr<Trader>> takers;
  // order book
  std::unique_ptr<OrderBook> book;
  // market data (trade/price history, etc.)
  std::unique_ptr<MarketData> market_data;
  
};