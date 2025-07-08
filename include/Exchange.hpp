// Exchange.hpp
// Simulate exchange
#pragma once
#include "MarketData.hpp"
#include "OrderBook.hpp"
#include "Trader.hpp"
#include <vector>
#include <memory>
#include <concepts>

template<typename T>
concept DerivedTrader = std::is_base_of<Trader, T>::value;

class Exchange {
public:
  Exchange() = delete;
  Exchange(float _starting_price = 100);
  ~Exchange();

  void add_maker(const Trader &maker);
  void add_taker(const Trader &taker);

  /**
   * @brief autogenerate maker
   * 
   * @tparam T trader subclass
   */
  template <DerivedTrader T>
  void add_maker();
  
  /**
   * @brief autogenerate taker
   * 
   * @tparam T trader subclass
   */
  template <DerivedTrader T>
  void add_taker();

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