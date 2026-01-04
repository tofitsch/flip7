#pragma once

#include "player.h"

namespace flip7 {

  class Game {

    public:

      Game() = delete;

      Game(std::vector<Player> const _players)
        : players{_players}, n_players{_players.size()} {

        for (size_t i = 0; i < n_players; ++i) {

          players[i].id = i;

          player_pointers.push_back(& players[i]);

        }

      }

      void play_game();

      bool
        print_each_draw{false},
        print_each_round{false},
        print_each_game{false},
        step_by_step{false};

    private:

      void print() const;

      void play_round();

      void confirm() const;

      void deal(char const card, Player * const p);

      void deactivate(Player * const p);

      Player * get_winner();

      Player * const get_active_player_with_highest_score_except(Player const * const except) const;
      Player * const get_active_player_with_lowest_score_and_no_heart_except(Player const * const except) const;

      std::vector<Player> players;

      std::vector<Player *> player_pointers;

      size_t 
        n_players,
        n_active,
        i_round{0},
        i_round_this_game{0},
        i_game{0};

      Deck deck;

  };

}
