#ifndef LTL_CHECKER_TS_H
#define LTL_CHECKER_TS_H

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

template <typename StateType, typename ActionType, typename APType>
class TransitionSystem {
 public:
  class Node {
   public:
    explicit Node(StateType state) : state_(state) {}
    ~Node() = default;

    const StateType& state() const { return state_; }

    const std::unordered_set<Node*>& Successors(ActionType action) const {
      static const std::unordered_set<Node*> empty_set;
      auto it = transitions_.find(action);
      if (it != transitions_.end()) {
        return it->second;
      }
      return empty_set;
    }

    std::unordered_set<Node*>& Successors(ActionType action) { return transitions_[action]; }

    const std::unordered_set<APType>& label() const { return label_; }
    std::unordered_set<APType>& label() { return label_; }

   private:
    StateType state_;
    std::unordered_map<ActionType, std::unordered_set<Node*>> transitions_;
    std::unordered_set<APType> label_;
  };

  TransitionSystem() = default;
  ~TransitionSystem() = default;

  const std::vector<Node>& nodes() const { return nodes_; }
  std::vector<Node>& nodes() { return nodes_; }
  const std::vector<ActionType>& actions() const { return actions_; }
  std::vector<ActionType>& actions() { return actions_; }
  const std::vector<const Node*>& initial_states() const { return initial_states_; }
  std::vector<const Node*>& initial_states() { return initial_states_; }

 private:
  std::vector<Node> nodes_;
  std::vector<ActionType> actions_;
  std::vector<const Node*> initial_states_;
};

TransitionSystem<size_t, size_t, std::string> ReadTransitionSystem(
    std::istream& is, std::vector<std::string>& atomic_propositions);

#endif  // LTL_CHECKER_TS_H
