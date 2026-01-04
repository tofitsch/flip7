#include "game.h"

namespace flip7 {

  void Game::print() const {

    std::cout 
      << "game: "
      << i_game
      << " round: "
      << i_round_this_game
      << std::endl
      << std::endl;

    static std::string const
      line_short(73, '-'),
      line_long(97, '-');

    std::cout
      << "player"
      << " | n_games_won"
      << " | n_rounds_scored"
      << " | avg_round_score"
      << " | avg_game_score";

    if (print_each_draw)
      std::cout
        << " | status"
        << " | score"
        << " | hand"
        << std::endl
        << line_long
        << std::endl;
    else
      std::cout
        << std::endl
        << line_short
        << std::endl;

    for (Player const& p : players)
      p.print(print_each_draw);

    std::cout << std::endl;

  }

  void Game::play_game() {

    ASSERT(n_players > 0);

    i_round_this_game = 0;

    std::shuffle(player_pointers.begin(), player_pointers.end(), g_rnd);

    ++i_game;

    for (Player & p : players) {

      ++p.stats.n_games;

      p.score = 0;

    }

    size_t max_score{0};

    if (n_players == 1)
      play_round();
    else do {

      play_round();

      std::rotate(player_pointers.begin(), player_pointers.begin() + 1, player_pointers.end());

    } while (! get_winner());

    ++(get_winner()->stats.n_wins);

    for (Player & p : players)
      p.stats.avg_game_score_numerator += p.score;
 
    if (print_each_game) {

      system("clear");

      std::cout << std::endl;

      print();

    }

  }

  Player * Game::get_winner() {

    Player * max_score_player = player_pointers.at(0);

    for (Player * p : player_pointers)
      if (p->score > max_score_player->score)
        max_score_player = p;
                        
    if (max_score_player->score >= 200) {

      for (Player * p : player_pointers)
        if (p != max_score_player && p->score == max_score_player->score)
          return nullptr; //no ties

      return max_score_player;

    }

    return nullptr;

  }

  void Game::play_round() {

    ++i_round;
    ++i_round_this_game;

    deck.init();

    for (Player & p : players) {

      p.is_active = true;

      ++p.stats.n_rounds;

    }

    n_active = n_players;

    while (n_active > 0) {

      for (Player & p : players) {
        if (p.is_active && i_round_this_game > 1) {

          if (! p.strategy(& p)) {

            p.add_to_score();

            deactivate(& p);

          }

        }
      }

      for (Player * p : player_pointers) {

        if(! p->is_active)
          continue;

        char const card = deck.draw();

        deal(card, p);

        if (print_each_draw) {

          system("clear");

          std::cout
            << "player "
            << p->id
            << " receives "
            << g_card_names[card]
            << std::endl;

          print();

          if (step_by_step)
            confirm();

        }

      }

    }

    if (print_each_draw || print_each_round) {

      system("clear");

      std::cout << std::endl;

      print();

    }

  }

  void Game::deactivate(Player * const p) {

    ASSERT(n_active > 0);

    p->is_active = false;

    for (char const card : p->hand)
      deck.discard(card);

    p->hand = {};

    --n_active;

  }

  void Game::deal(char const card, Player * const p) {

    if (card == 19) { // flip3

      Player * receiver =
        n_active > 1
        ? get_active_player_with_highest_score_except(p)
        : p;

      for (size_t i = 0; i < 3; ++i) {

        deal(deck.draw(), receiver);

        if (! receiver->is_active)
          break;

      }

    } else if (card == 20) { // freeze

      if (n_active == 1)
        deactivate(p);
      else
        deactivate(get_active_player_with_highest_score_except(p));

    } else if (card == 21 && p->hand.contains(21)) { // heart if p already has one

      Player * receiver = get_active_player_with_lowest_score_and_no_heart_except(p);

      if (! receiver)
        deck.discard(card);
      else
        receiver->take(card);

    } else { // regular number card, heart, or bonus card

      p->take(card);

      if (! p->is_active)
        deactivate(p);

    }

  }

  Player * const Game::get_active_player_with_highest_score_except(Player const * const except) const {

    Player * candidate{nullptr};

    for (Player * p : player_pointers) {

      if (p == except || ! p->is_active)
        continue;

      if (! candidate)
        candidate = p;

      if (
           candidate->score < p->score
           || (candidate->score == p->score && candidate->get_hand_score() < p->get_hand_score())
         )
        candidate = p;

    }

    ASSERT(candidate != nullptr);

    return candidate;

  }

  Player * const Game::get_active_player_with_lowest_score_and_no_heart_except(Player const * const except) const {

    Player * candidate{nullptr};

    for (Player * p : player_pointers) {

      if (p == except || ! p->is_active || p->hand.contains(21))
        continue;

      if (! candidate)
        candidate = p;

      if (
           candidate->score > p->score
           || (candidate->score == p->score && candidate->get_hand_score() > p->get_hand_score())
         )
        candidate = p;

    }

    return candidate;

  }

  void Game::confirm() const {

    std::cout 
      << std::endl
      << "(Enter to continue)"
      << std::endl;

    std::cin.get();

  }

}
