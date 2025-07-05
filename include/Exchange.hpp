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
  Exchange();
  ~Exchange();

  void run();
private:
  std::vector<std::unique_ptr<Trader>> makers;
  std::vector<std::unique_ptr<Trader>> takers;
  std::unique_ptr<OrderBook> book;
  std::unique_ptr<MarketData> market_data;
  
};