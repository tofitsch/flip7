#include "player.h"

namespace flip7 {

  int Player::print(int row, bool const print_each_draw) const {

    int col = 0;

    mvprintw(
      row, col,
      "%-7lu| %-12zu| %-16zu| %-8zu| %-16.2f| %-15.2f",
      id,
      stats.n_wins,
      stats.n_rounds_scored,
      stats.n_flip7,
      static_cast<float>(stats.avg_round_score_numerator) / static_cast<float>(stats.n_rounds),
      static_cast<float>(stats.avg_game_score_numerator) / static_cast<float>(stats.n_games)
    );

    col += 7 + 1 + 13 + 1 + 17 + 1 + 9 + 1 + 17 + 1 + 16;

    if (print_each_draw) {

        mvprintw(row, col, "| %-7s| %-6lu| ", is_active ? "in" : "out", score);

        col += 1 + 8 + 1 + 7 + 1 + 2;

    }

    bool first = true;

    for (char const card : hand) {

      mvprintw(row, col, "%s%s", first ? "" : " ", g_card_names[card].c_str());

      col += (first ? 0 : 1) + g_card_names[card].length();

      first = false;

    }

    return row + 1;

  }

  void Player::take(char const card) {

    if (card <= 12) { // normal card

      is_active = hand.insert(card).second;

      if (! is_active && hand.contains(21)) { // saved by heart

        hand.erase(21);

        is_active = true;

      }

    } else if (card <= 18) // plus and x2 bonus cards
      hand.insert(card);
    else if (card == 21) // heart
      ASSERT(hand.insert(card).second); // case where heart already on hand must be handled outside
    else 
      ASSERT(false); // flip3 and freeze must be handled outside

  }

  std::pair<size_t, size_t> Player::get_hand_score_pair() const {

    size_t points{0}, bonus{0};

    bool has_x2{false};

    for (char const card : hand) {

      switch (card) {

        // bonus plus
        case 13: bonus +=  2; break;
        case 14: bonus +=  4; break;
        case 15: bonus +=  6; break;
        case 16: bonus +=  8; break;
        case 17: bonus += 10; break;

        // bonus x2
        case 18: has_x2 = true; break;

        default:
          if (card <= 12) // normal card
            points += card;
          break;

      };

    }

    if (has_x2)
      points *= 2;

    return {points, bonus};

  }

  size_t Player::n_regular_cards_on_hand() const {

    size_t n{0};

    for (char const card : hand)
      if (card <= 12)
        ++n;

    return n;

  }

  size_t Player::get_hand_score() const {

    std::pair<size_t, size_t> hand_score = get_hand_score_pair();

    return hand_score.first + hand_score.second;

  }

  void Player::add_to_score(bool const is_flip7) {

    size_t round_score = get_hand_score();

    if (is_flip7) {

      round_score += 15;

      ++stats.n_flip7;

    }

    stats.avg_round_score_numerator += round_score;

    ++stats.n_rounds_scored;

    score += round_score;

  }

}
