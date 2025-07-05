// Trader.hpp
#pragma once
#include <string>
#include <unordered_map>
#include <tuple>

using SYMBOL = std::string;

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
  ~Trader() = default;

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
   * @brief Let Trader make trade
   * 
   * @return std::tuple<float, int> 
   */
  virtual std::tuple<float, int> trade() const;
  
  virtual float fair_price() const;

  /**
   * @brief Equality operator
   * 
   * @param other 
   * @return true 
   * @return false 
   */
  bool operator==(const Trader &other) const;
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
   * @brief Let Trader make trade
   * 
   * @return std::tuple<float, int> 
   */
  std::tuple<float, int> trade() const override;
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
   * @brief Let Trader make trade
   * 
   * @return std::tuple<float, int> 
   */
  std::tuple<float, int> trade() const override;
};


