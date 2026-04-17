#ifndef LTL_CHECKER_PERSISTENCE_CHECKER_H
#define LTL_CHECKER_PERSISTENCE_CHECKER_H

#include <boost/dynamic_bitset.hpp>

#include "gnba.h"
#include "ts.h"

class PersistenceChecker {
 public:
  static bool Check(
      const TransitionSystem<std::pair<size_t, GNBA<boost::dynamic_bitset<>>::TaggedState>, size_t,
                             const GNBA<GNBA<boost::dynamic_bitset<>>::TaggedState>::Node*>& ts,
      const GNBA<GNBA<boost::dynamic_bitset<>>::TaggedState>& nba);
};

#endif  // LTL_CHECKER_PERSISTENCE_CHECKER_H
