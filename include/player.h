#pragma once

#include <set>
#include <assert.h>
#include <functional>
#include <iomanip>

#include "stats.h"
#include "deck.h"

namespace flip7 {

  class Player {

    public:

      using Strategy = std::function<bool(Player const * const)>;

      Player() = delete;

      Player(Strategy _strategy)
        : strategy(std::move(_strategy)) {}

      void print(bool const print_each_draw = false) const;

      void take(char const card);

      void add_to_score();

      std::pair<size_t, size_t> get_hand_score_pair() const;

      inline float regular_points() const
        {return get_hand_score_pair().first;}

      inline float bonus_points() const
        {return get_hand_score_pair().second;}

      size_t get_hand_score() const;

      std::set<char> hand;

      bool is_active;

      size_t
        id{0},
        score{0};

      Stats stats;

      Strategy strategy;

  };

}
