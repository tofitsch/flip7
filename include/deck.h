#pragma once

#include <vector>
#include <array>
#include <random>
#include <iostream>
#include <algorithm>

#include "assert.h"

namespace flip7 {

  static std::random_device g_rnd_dev;
  static std::mt19937 g_rnd(g_rnd_dev());

  static std::array<std::string, 22> const g_card_names = {
    "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", // 0 - 12
    "+2", "+4", "+6", "+8", "+10", // 13 - 17
    "x2",     // 18
    "flip3",  // 19 
    "freeze", // 20 
    "heart",  // 21 
  };

  static std::array<char, 79 + 6 + 9> const g_init_deck = {
     0,
     1,
     2,  2,
     3,  3,  3,
     4,  4,  4,  4,
     5,  5,  5,  5,  5,
     6,  6,  6,  6,  6,  6,
     7,  7,  7,  7,  7,  7,  7,
     8,  8,  8,  8,  8,  8,  8,  8,
     9,  9,  9,  9,  9,  9,  9,  9,  9,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11,
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    13, 14, 15, 16, 17,
    18,
    19, 19, 19,
    20, 20, 20,
    21, 21, 21,
  };

  class Deck {

    public:

      Deck() {init();}

      void init();

      char draw();

      void discard(char const card);

    private:

      std::vector<char>
        draw_pile,
        discard_pile;

  };

}
