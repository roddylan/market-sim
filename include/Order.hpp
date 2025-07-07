// Order.hpp
// Order object
#pragma once

#include "Trader.hpp"
#include <memory>
#include <chrono>
#include "MarketUtils.hpp"

/**
 * @class Order
 * @brief Represents Order
 *
 * Class stores order information, negative volume for short/sell and positive
 * volume for long/buy
 */
class Order {
public:
  // deleted default/empty constructor
  Order() = delete;
  
  /**
   * @brief Destroy the Order object (default)
   * 
   */
  ~Order() = default;
  
  /**
   * @brief Construct a new Order object
   * 
   * @param _price 
   * @param _volume 
   * @param _trader 
   */
  Order(float _price, int _volume, Trader &_trader);

  /**
   * @brief Construct a new Order object
   * 
   * @param _price 
   * @param _volume 
   * @param _trader 
   */
  Order(float _price, int _volume, const Trader* const _trader);

  /**
   * @brief Construct a new Order object
   * 
   * @param _price 
   * @param _volume 
   * @param _trader 
   * @param _timestamp 
   */
  Order(float _price, int _volume, Trader &_trader, const MarketUtils::Timestamp &_timestamp);
  
  Order(float _price, int _volume, const Trader* const _trader, const MarketUtils::Timestamp &_timestamp);

  /**
   * @brief Construct a new Order object
   * 
   * @param other 
   */
  Order(const Order &other);
  
  // deleted assignment operator
  Order &operator=(const Order &) = delete;
  
  // getters
  /**
   * @brief Get the bid/ask price of the order
   * 
   * @return float 
   */
  float get_price() const noexcept;
  
  /**
   * @brief Get the volume of the trade. < 0 if short/sell, > 0 if long/buy
   * 
   * @return int 
   */
  int get_volume() const noexcept;
  
  /**
   * @brief Get the trader object
   * 
   * @return Trader& 
   */
  const Trader &get_trader() const noexcept;

  /**
   * @brief Get the time object
   * 
   * @return std::chrono::time_point<std::chrono::steady_clock> 
   */
  MarketUtils::Timestamp get_time() const noexcept;

  /**
   * @brief update volume
   * 
   * @param inc 
   */
  void update_volume(const int &inc);

  // comparison ops
  /**
   * @brief Equality comparison operator
   * 
   * @param other 
   * @return true 
   * @return false 
   */
  bool operator==(const Order &other) const;
private:
  
  float price;
  int volume;
  const Trader* const trader;
  const MarketUtils::Timestamp timestamp; // uint_8 
};
