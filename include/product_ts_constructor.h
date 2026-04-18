#ifndef LTL_CHECKER_PRODUCT_H
#define LTL_CHECKER_PRODUCT_H

#include <boost/dynamic_bitset.hpp>

#include "gnba.h"
#include "ts.h"

class ProductTSConstructor {
 public:
  using TSType = TransitionSystem<size_t, size_t, std::string>;
  using NBAStateType = GNBA<boost::dynamic_bitset<>>::TaggedState;
  using NBAType = GNBA<NBAStateType>;
  using ProductTSType =
      TransitionSystem<std::pair<size_t, NBAStateType>, size_t, const NBAType::Node*>;

  static ProductTSType Build(const TSType& ts, const NBAType& nba, int ts_initial_state_id);
};

#endif  // LTL_CHECKER_PRODUCT_H
