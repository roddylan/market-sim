// Order.hpp
// Order object
#pragma once

#include "Trader.hpp"
#include <memory>
#include <chrono>

/**
 * @class Order
 * @brief Represents Order
 *
 * Class stores order information, negative volume for short/sell and positive
 * volume for long/buy
 */
class Order {
public:
  using Timestamp = std::chrono::time_point<std::chrono::steady_clock>;
  
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
  Timestamp get_time() const noexcept;

  
  void set_time();

  /**
   * @brief update volume
   * 
   * @param inc 
   */
  void update_volume(const int &inc);

  // comparisons
  bool operator<(const Order &other) const noexcept;
  bool operator>(const Order &other) const noexcept;
  bool operator==(const Order &other) const noexcept;
private:
  
  float price;
  int volume;
  Trader* const trader;
  const Timestamp timestamp; // uint_8 
};
