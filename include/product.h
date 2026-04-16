#ifndef LTL_CHECKER_PRODUCT_H
#define LTL_CHECKER_PRODUCT_H

#include "ts.h"

template <typename TSStateType, typename ActionType, typename NBAStateType>
TransitionSystem<std::pair<TSStateType, NBAStateType>, ActionType,
                 const typename GNBA<NBAStateType>::Node*>
Product(const TransitionSystem<TSStateType, ActionType, std::string>& ts,
        const GNBA<NBAStateType>& nba) {
  // Require that nba is indeed an NBA.

  using TSNode = typename TransitionSystem<TSStateType, ActionType, std::string>::Node;
  using NBANode = typename GNBA<NBAStateType>::Node;
  using ProductTSType =
      TransitionSystem<std::pair<TSStateType, NBAStateType>, ActionType, const NBANode*>;

  ProductTSType product_ts;

  using NodeMapKey = std::pair<const TSNode*, const NBANode*>;

  struct NodeMapKeyHash {
    size_t operator()(const NodeMapKey& key) const {
      return std::hash<const TSNode*>()(key.first) ^ (std::hash<const NBANode*>()(key.second) << 1);
    }
  };

  std::unordered_map<NodeMapKey, size_t, NodeMapKeyHash> node_map;

  // Create nodes for the product TS.
  product_ts.nodes().reserve(ts.nodes().size() * nba.nodes().size());
  for (const auto& ts_node : ts.nodes()) {
    for (const auto& nba_node : nba.nodes()) {
      product_ts.nodes().emplace_back(std::make_pair(ts_node.state(), nba_node.state()));
      product_ts.nodes().back().label().insert(&nba_node);
      node_map[{&ts_node, &nba_node}] = product_ts.nodes().size() - 1;
    }
  }

  // Set actions.
  product_ts.actions() = ts.actions();

  // Set initial states.
  for (const auto* ts_init : ts.initial_states()) {
    for (const auto* nba_init : nba.initial_states()) {
      if (ts_init->label() == nba_init->label()) {
        for (const auto* nba_succ : nba_init->successors()) {
          product_ts.initial_states().push_back(&product_ts.nodes()[node_map[{ts_init, nba_succ}]]);
        }
      }
    }
  }

  // Set transitions.
  for (const auto& ts_node : ts.nodes()) {
    for (const auto& action : ts.actions()) {
      for (const auto* ts_succ : ts_node.Successors(action)) {
        for (const auto& nba_node : nba.nodes()) {
          if (nba_node.label() == ts_succ->label()) {
            for (const auto* nba_succ : nba_node.successors()) {
              product_ts.nodes()[node_map[{&ts_node, &nba_node}]].Successors(action).insert(
                  &product_ts.nodes()[node_map[{ts_succ, nba_succ}]]);
            }
          }
        }
      }
    }
  }

  return product_ts;
}

#endif  // LTL_CHECKER_PRODUCT_H
