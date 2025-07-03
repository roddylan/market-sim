// Position.hpp
#ifndef _POSITION_HPP
#define _POSITION_HPP
namespace {
  using size_t = unsigned int;
  struct Position {
    Position(size_t _vol, float _init_price) : vol{_vol}, init_price{_init_price} {}
    
    size_t vol;
    float init_price;
  };

};

#endif