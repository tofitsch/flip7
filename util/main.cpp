#include "game.h"

/*
 A strategy is a set of rules based on which the player decides to continue (return true) or pass (return false) before each round.
 Define strategies here and add them as players further below.

 For the sake of simplicity any other decision like whom to give a freeze or flip7 are done the same (regardless of strategy): always to the player with the highest score in the current game, and the one with the highest number of points on their hand if therer is a tie.
*/

// t:20, w:0
auto strategy_1 = [](flip7::Player const * const p) -> bool {

  if (p->regular_points() >= 20.)
    return false;

  return true;

};

// t:25,
auto strategy_2 = [](flip7::Player const * const p) -> bool {

  if (p->regular_points() >= 25.)
    return false;

  return true;

};

// t:25, w:0.5
auto strategy_3 = [](flip7::Player const * const p) -> bool {

  if (p->regular_points() + p->bonus_points() * .5 >= 25.)
    return false;

  return true;

};

// coin flip
auto strategy_4 = [](flip7::Player const * const p) -> bool {

  static std::bernoulli_distribution b_dist(.5);

  return b_dist(flip7::g_rnd);

};

int main() {

  size_t const n_games = 1000; // number of games to play

 // Add strategies here, each will be one player in the game
 // At the start of each game their order is shuffled.
 // Therefore it does not matter in which order they are defined.
  flip7::Game game {{
    {strategy_1},
    {strategy_2},
    {strategy_3},
  }};

  // Some options to configure.
  // These do not change the final result, only how often the display updates.
  // Set all to false for fastest results, some to true to watch the game play out.
  game.print_each_draw    = false;
  game.print_each_round   = true;
  game.print_each_game    = false;
  // Enable/disable 'press Enter to continue' after each step
  game.confirm_each_draw  = false;
  game.confirm_each_round = false;
  game.confirm_each_game  = false;

  // Run the games
  for (size_t i_game = 0; i_game < n_games; ++i_game)
    game.play_game();
  
}
