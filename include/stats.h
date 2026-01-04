#pragma once

namespace flip7 {

  class Stats {

    public:

      size_t
        n_wins{0},
        n_games{0},
        n_rounds{0},
        n_flip7{0},
        n_rounds_scored{0},
        avg_game_score_numerator{0},
        avg_round_score_numerator{0};

  };

}
