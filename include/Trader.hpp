// Trader.hpp
#pragma once
#include <string>
#include <random>

using SYMBOL = std::string;

// forward declaring Order and Exchange
// avoid circular dependency
class Order;
class Exchange;

/**
 * @class Trader
 * @brief Trader base class
 * 
 */
class Trader {
public:
  /**
   * @brief Construct a new Trader object
   * 
   */
  Trader() = default;
  /**
   * @brief Destroy the Trader object
   * 
   */
  virtual ~Trader() = default;

  /**
   * @brief Construct a new Trader object
   * 
   * @param _name 
   */
  Trader(const std::string &_name);
  /**
   * @brief Construct a new Trader object
   * 
   * @param other 
   */
  Trader(const Trader &other);
  /**
   * @brief Assignment
   * 
   * @param rhs 
   * @return Trader& 
   */
  Trader &operator=(const Trader &rhs);

  /**
   * @brief Get the name object
   * 
   * @return const std::string& 
   */
  const std::string &get_name() const;
  
  /**
   * @brief Set the name object
   * 
   * @param _name 
   */
  void set_name(const std::string &_name);

  /**
   * @brief Set rng seed
   * 
   * @param seed 
   */
  void set_random(int seed);

  /**
   * @brief Generate order from trader
   * 
   * @param exchange 
   * @param is_long 
   * @return Order 
   */
  virtual Order make_order(const Exchange *exchange, bool is_long = false) const;

  /**
   * @brief generate fair price from exchange
   * 
   * @param exchange Exchange
   * @return float 
   */
  virtual float fair_price(const Exchange *exchange) const;

  /**
   * @brief Equality operator
   * 
   * @param other 
   * @return true 
   * @return false 
   */
  bool operator==(const Trader &other) const;
protected:
  mutable std::mt19937 gen;
private:
  std::string name;
};

/**
 * @brief Market Maker (Random)
 * 
 */
class MMakerTrader : public Trader {
public:
  /**
   * @brief Construct a new MMakerTrader object
   * 
   * @param _name 
   */
  MMakerTrader(const std::string &_name);

  /**
   * @brief Generate order from trader
   * 
   * @param exchange 
   * @param is_long 
   * @return Order 
   */
  Order make_order(const Exchange *exchange, bool is_long = false) const override;

  /**
   * @brief generate fair price from exchange
   * 
   * @param exchange Exchange
   * @return float 
   */
  float fair_price(const Exchange *exchange) const override;
};

/**
 * @brief Market Taker (Random)
 * 
 */
class MTakerTrader : public Trader {
public:
  /**
   * @brief Construct a new MTakerTrader object
   * 
   * @param _name 
   */
  MTakerTrader(const std::string &_name);

  /**
   * @brief Generate order from trader
   * 
   * @param exchange 
   * @param is_long 
   * @return Order 
   */
  Order make_order(const Exchange *exchange, bool is_long = false) const override;
  // Order make_order(float fair_price, bool is_long = false) const override;

  /**
   * @brief generate fair price from exchange
   * 
   * @param exchange Exchange
   * @return float 
   */
  float fair_price(const Exchange *exchange) const override;
};


