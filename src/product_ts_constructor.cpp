#include "product_ts_constructor.h"

// Step 4: Product construction between transition system and NBA (Definition 4.62, Page 200)
// Builds the synchronous product of the given TS and the NBA.
ProductTSConstructor::ProductTSType ProductTSConstructor::Build(const TSType& ts,
                                                                const NBAType& nba,
                                                                int ts_initial_state_id) {
  ProductTSType product_ts;

  using NodeMapKey = std::pair<const TSType::Node*, const NBAType::Node*>;

  struct NodeMapKeyHash {
    size_t operator()(const NodeMapKey& key) const {
      return std::hash<const TSType::Node*>()(key.first) ^
             (std::hash<const NBAType::Node*>()(key.second) << 1);
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
  if (ts_initial_state_id == -1) {
    for (const auto* ts_init : ts.initial_states()) {
      for (const auto* nba_init : nba.initial_states()) {
        if (ts_init->label() == nba_init->label()) {
          for (const auto* nba_succ : nba_init->successors()) {
            product_ts.initial_states().push_back(
                &product_ts.nodes()[node_map[{ts_init, nba_succ}]]);
          }
        }
      }
    }
  } else {
    const auto* ts_init = &ts.nodes()[ts_initial_state_id];
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