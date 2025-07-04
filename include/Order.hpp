// Order.hpp
// Order object
#ifndef _ORDER_HPP
#define _ORDER_HPP
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
  
  // deleted default/empty constructor
  Order() = delete;
  
  /**
   * @brief Destroy the Order object (default)
   * 
   */
  ~Order();
  
  /**
   * @brief Construct a new Order object
   * 
   * @param _price 
   * @param _volume 
   * @param _maker 
   */
  Order(float _price, int _volume, Trader &_maker);

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
   * @brief Get the maker object
   * 
   * @return Trader& 
   */
  Trader &get_maker() const noexcept;

  /**
   * @brief Execute order (partially or fully)
   * 
   * @param req_vol requested trade volume
   * @return int volume traded
   */
  int make_trade(const int req_vol);

  // comparisons
  bool operator<(const Order &other);
  bool operator>(const Order &other);
  bool operator==(const Order &other);
private:
  /**
   * @brief Execute sell order (maker selling, taker buying)
   * 
   * @param req_vol 
   * @return int 
   */
  int sell_trade(const int req_vol);
  
  /**
   * @brief Execute buy order (maker buying, taker selling)
   * 
   * @param req_vol 
   * @return int 
   */
  int buy_trade(const int req_vol);
  
  float price;
  int volume;
  Trader* const maker;
  const std::chrono::time_point<std::chrono::steady_clock> timestamp; // uint_8 
};

#endif