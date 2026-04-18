#ifndef LTL_CHECKER_PERSISTENCE_CHECKER_H
#define LTL_CHECKER_PERSISTENCE_CHECKER_H

#include <boost/dynamic_bitset.hpp>

#include "gnba.h"
#include "ts.h"

class PersistenceChecker {
 public:
  using GNBAType = GNBA<boost::dynamic_bitset<>>;
  using NBAState = GNBAType::TaggedState;
  using NBAType = GNBA<NBAState>;
  using ProductTSType = TransitionSystem<std::pair<size_t, NBAState>, size_t, const NBAType::Node*>;
  using ProductTSNode = ProductTSType::Node;

  static bool Check(const ProductTSType& ts, const NBAType& nba);

 private:
  static bool CycleCheck(const ProductTSNode* start, const ProductTSType& ts,
                         std::unordered_set<const ProductTSNode*>& inner_visited);
};

#endif  // LTL_CHECKER_PERSISTENCE_CHECKER_H
