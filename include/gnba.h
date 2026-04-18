#ifndef LTL_CHECKER_GNBA_H
#define LTL_CHECKER_GNBA_H

#include <unordered_set>
#include <vector>

// GNBA class specialized for LTL checker.
template <typename StateType>
class GNBA {
 public:
  class Node {
   public:
    explicit Node(StateType state) : state_(state) {}
    ~Node() = default;

    const StateType& state() const { return state_; }
    const std::unordered_set<std::string>& label() const { return label_; }
    std::unordered_set<std::string>& label() { return label_; }
    const std::unordered_set<Node*>& successors() const { return successors_; }
    std::unordered_set<Node*>& successors() { return successors_; }

   private:
    // The only possible transition is \delta(state, label) = successors.
    StateType state_;
    std::unordered_set<std::string> label_;
    std::unordered_set<Node*> successors_;
  };

  struct TaggedState {
    StateType state_;
    size_t acceptance_id_;
  };

  GNBA() = default;
  ~GNBA() = default;
  GNBA(GNBA&&) noexcept = default;
  GNBA& operator=(GNBA&&) noexcept = default;
  GNBA(const GNBA&) = delete;
  GNBA& operator=(const GNBA&) = delete;

  const std::vector<Node>& nodes() const { return nodes_; }
  std::vector<Node>& nodes() { return nodes_; }
  const std::vector<const Node*>& initial_states() const { return initial_states_; }
  std::vector<const Node*>& initial_states() { return initial_states_; }
  const std::vector<std::unordered_set<const Node*>>& acceptance_sets() const {
    return acceptance_sets_;
  }
  std::vector<std::unordered_set<const Node*>>& acceptance_sets() { return acceptance_sets_; }

  void EnsureDefaultAcceptanceSet() {
    if (acceptance_sets_.empty()) {
      std::unordered_set<const Node*> all_nodes;
      for (size_t i = 0; i < nodes_.size(); ++i) {
        all_nodes.insert(&nodes_[i]);
      }
      acceptance_sets_.push_back(std::move(all_nodes));
    }
  }

  // Step 3: Equivalent conversion from GNBA to NBA
  // Converts the Generalized NBA to an equivalent Non-deterministic Buchi Automaton (NBA).
  GNBA<TaggedState> ToNBA() const {
    // Require that acceptance_sets_ is not empty.
    GNBA<TaggedState> nba;
    size_t k = acceptance_sets_.size();

    auto get_gnba_node_id = [this](const Node* node) -> size_t { return node - nodes_.data(); };

    auto get_nba_node_id = [this](size_t gnba_node_id, size_t acceptance_id) -> size_t {
      return gnba_node_id + acceptance_id * nodes_.size();
    };

    // Create states Q' = Q x {0, 1, ..., k-1}
    nba.nodes().reserve(nodes_.size() * k);
    for (size_t j = 0; j < k; ++j) {
      for (size_t i = 0; i < nodes_.size(); ++i) {
        nba.nodes().emplace_back(
            typename GNBA<TaggedState>::Node(TaggedState{nodes_[i].state(), j}));
        nba.nodes().back().label() = nodes_[i].label();
      }
    }

    // Set initial states Q'_0 = Q_0 x {0}
    for (const auto* initial_state : initial_states_) {
      nba.initial_states().push_back(
          &nba.nodes()[get_nba_node_id(get_gnba_node_id(initial_state), 0)]);
    }

    // Set acceptance state F' = F_0 x {0}
    std::unordered_set<const typename GNBA<TaggedState>::Node*> nba_acceptance_set;
    for (const auto* f0_node : acceptance_sets_[0]) {
      nba_acceptance_set.insert(&nba.nodes()[get_nba_node_id(get_gnba_node_id(f0_node), 0)]);
    }
    nba.acceptance_sets().push_back(nba_acceptance_set);

    // Add transitions
    for (size_t j = 0; j < k; ++j) {
      for (size_t i = 0; i < nodes_.size(); ++i) {
        size_t next_acceptance_id = acceptance_sets_[j].count(&nodes_[i]) > 0 ? (j + 1) % k : j;
        for (const auto* successor : nodes_[i].successors()) {
          nba.nodes()[get_nba_node_id(i, j)].successors().insert(
              &nba.nodes()[get_nba_node_id(get_gnba_node_id(successor), next_acceptance_id)]);
        }
      }
    }

    return nba;
  }

 private:
  std::vector<Node> nodes_;
  std::vector<const Node*> initial_states_;
  std::vector<std::unordered_set<const Node*>> acceptance_sets_;
};

#endif  // LTL_CHECKER_GNBA_H
