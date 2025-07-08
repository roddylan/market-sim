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

/**
 * @brief Trader subclass
 * 
 * @tparam T 
 */
template<typename T>
concept DerivedTrader = std::is_base_of<Trader, T>::value;

/**
 * @class Exchange
 * @brief Represents Exchange
 * 
 * Orchestrates trader actions, stores and handles Traders (market makers/takers)
 */
class Exchange {
public:
  using Traders = std::vector<std::shared_ptr<Trader>>;

  Exchange(float _starting_price = 100);
  ~Exchange() = default;

  /**
   * @brief Get market makers
   * 
   * @return Traders 
   */
  Traders get_makers() const;
  
  /**
   * @brief Get market takers
   * 
   * @return Traders 
   */
  Traders get_takers() const;

  /**
   * @brief Add market maker
   * 
   * @param maker 
   */
  void add_maker(const Trader &maker);
  /**
   * @brief Add market taker
   * 
   * @param taker 
   */
  void add_taker(const Trader &taker);

  /**
   * @brief autogenerate maker
   * 
   * @tparam T trader subclass
   */
  template <DerivedTrader T>
  void add_maker() {
    makers.push_back(std::make_shared<T>(std::to_string(makers.size()+1)));
  }
  
  /**
   * @brief autogenerate taker
   * 
   * @tparam T trader subclass
   */
  template <DerivedTrader T>
  void add_taker() {
    takers.push_back(std::make_shared<T>(std::to_string(takers.size()+1)));
  }

  /**
   * @brief Get the book object
   * 
   * @return const OrderBook& 
   */
  const OrderBook &get_book() const;

  /**
   * @brief Get the market data object
   * 
   * @return const MarketData& 
   */
  const MarketData &get_market_data() const;
  
  /**
   * @brief Set the starting price
   * 
   * @param price 
   */
  void set_starting_price(float price);
  
  /**
   * @brief Get the starting price
   * 
   * @return float 
   */
  float get_starting_price() const;

  /**
   * @brief Run tick
   * 
   */
  void run(); // TODO: add zero price check; end sim if 0
private:
  // traders
  Traders makers;
  Traders takers;
  // order book
  std::unique_ptr<OrderBook> book;
  // market data (trade/price history, etc.)
  std::unique_ptr<MarketData> market_data;

  float starting_price;
  
};