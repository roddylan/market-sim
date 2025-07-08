// Exchange.hpp
// Simulate exchange
#pragma once
#include "MarketData.hpp"
#include "OrderBook.hpp"
#include "Trader.hpp"
#include <string>
#include <vector>
#include <memory>
#include <concepts>

template<typename T>
concept DerivedTrader = std::is_base_of<Trader, T>::value;

class Exchange {
public:
  Exchange(float _starting_price = 100);
  ~Exchange() = default;

  void add_maker(const Trader &maker);
  void add_taker(const Trader &taker);

  /**
   * @brief autogenerate maker
   * 
   * @tparam T trader subclass
   */
  template <DerivedTrader T>
  void add_maker() {
    makers.push_back(std::make_shared<T>(std::to_string(maker_counter)));
    ++maker_counter;
  }
  
  /**
   * @brief autogenerate taker
   * 
   * @tparam T trader subclass
   */
  template <DerivedTrader T>
  void add_taker() {
    takers.push_back(std::make_shared<T>(std::to_string(maker_counter)));
    ++taker_counter;
  }

  const OrderBook &get_book() const;
  const MarketData &get_market_data() const;
  float get_starting_price() const;

  void run();
private:
  // traders
  std::vector<std::shared_ptr<Trader>> makers;
  std::vector<std::shared_ptr<Trader>> takers;
  // order book
  std::unique_ptr<OrderBook> book;
  // market data (trade/price history, etc.)
  std::unique_ptr<MarketData> market_data;

  size_t maker_counter;
  size_t taker_counter;

  float starting_price;
  
};