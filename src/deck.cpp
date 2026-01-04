#include "deck.h"

namespace flip7 {

  void Deck::init() {

    discard_pile = {};

    draw_pile.assign(g_init_deck.begin(), g_init_deck.end());

    std::shuffle(draw_pile.begin(), draw_pile.end(), g_rnd);

  };

  char Deck::draw() {

    char const card = draw_pile.back();

    draw_pile.pop_back();

    if (draw_pile.size() == 0) {

      draw_pile = discard_pile;

      discard_pile = {};

      std::shuffle(draw_pile.begin(), draw_pile.end(), g_rnd);

    }

    return card;

  }

  void Deck::discard(char const card) {

    discard_pile.push_back(card);

  }

}
