#include "game.h"

/*
 *** Instructions ***

 Any changes to game setup and player strategies should be made in this file.

 To ru the program first open a new terminal: File->New->Terminal (opens in new tab)

 in there type this to compile and run the program for the first time:

 cd build; cmake .. && make && ./x

 Press Enter to start

 Once the program finished running and presents the final results in a table, press Enter again to get back to the terminal.

 Then you can change something in this file again, save it, and back in the terminal tab type:

 make && ./x

 to run with the new configuration.

 **** Play strategies ***

 Below are a few example strategies one can use to play against each other.

 A strategy is a set of rules based on which the player decides to continue (return true) or pass (return false) before each round.
 Define strategies here and add them as players further below.

 For the sake of simplicity any other decision like whom to give a freeze or flip7 are done the same (regardless of strategy): always to the player with the highest score in the current game, and the one with the highest number of points on their hand if there is a tie.
*/

// t:20, w:0 (t stands for "threshold", w for "weight"))
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

// 50/50 coin flip
auto strategy_4 = [](flip7::Player const * const p) -> bool {

  static std::bernoulli_distribution b_dist(.5);

  return b_dist(flip7::g_rnd);

};

int main() {

  size_t const n_games = 100; // number of games to play

 // Add strategies here, each will be one player in the game
 // At the start of each game their order is shuffled.
 // Therefore it does not matter in which order they are defined.
  flip7::Game engine {{
    {strategy_1},
    {strategy_2},
    {strategy_3},
  }};

  // Some options to configure.
  // These do not change the final result, only how often the display updates.
  // Set all to false for fastest results, some to true to watch the game play out.
  engine.print_each_draw    = false;
  engine.print_each_round   = false;
  engine.print_each_game    = true;
  // Enable/disable 'press Enter to continue' after each card draw (for debugging)
  engine.step_by_step       = false;

  // end of configuration (don't change anything below here)

  // Run the games
  for (size_t i_game = 0; i_game < n_games; ++i_game)
    engine.play_game();

}
