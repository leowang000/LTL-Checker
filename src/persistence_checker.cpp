#include "persistence_checker.h"

#include <boost/dynamic_bitset.hpp>
#include <stack>
#include <unordered_set>

#include "gnba.h"
#include "ts.h"

bool PersistenceChecker::Check(
    const TransitionSystem<std::pair<size_t, GNBA<boost::dynamic_bitset<>>::TaggedState>, size_t,
                           const GNBA<GNBA<boost::dynamic_bitset<>>::TaggedState>::Node*>& ts,
    const GNBA<GNBA<boost::dynamic_bitset<>>::TaggedState>& nba) {
  using TSType =
      TransitionSystem<std::pair<size_t, GNBA<boost::dynamic_bitset<>>::TaggedState>, size_t,
                       const GNBA<GNBA<boost::dynamic_bitset<>>::TaggedState>::Node*>;
  using TSNode = TSType::Node;
  const auto& acceptance_set = nba.acceptance_sets()[0];
  std::unordered_set<const TSNode*> outer_visited;
  std::unordered_set<const TSNode*> inner_visited;
  std::stack<const TSNode*> outer_stack;
  for (const auto* ts_init : ts.initial_states()) {
    if (outer_visited.contains(ts_init)) {
      continue;
    }
    outer_stack.push(ts_init);
    outer_visited.insert(ts_init);
    while (!outer_stack.empty()) {
      const TSNode* cur = outer_stack.top();
      bool found_unvisited_successor = false;
      for (auto action : ts.actions()) {
        for (const auto* next : cur->Successors(action)) {
          if (!outer_visited.contains(next)) {
            outer_stack.push(next);
            outer_visited.insert(next);
            found_unvisited_successor = true;
            break;
          }
        }
        if (found_unvisited_successor) {
          break;
        }
      }
      if (found_unvisited_successor) {
        continue;
      }
      outer_stack.pop();
      if (acceptance_set.contains(*cur->label().begin())) {
        std::stack<const TSNode*> inner_stack;
        inner_stack.push(cur);
        inner_visited.insert(cur);
        while (!inner_stack.empty()) {
          const TSNode* inner_cur = inner_stack.top();
          for (auto action: ts.actions()) {
            if (inner_cur->Successors(action).contains(cur)) {
              return false;
            }
          }
          bool found_unvisited_successor_inner = false;
          for (auto action : ts.actions()) {
            for (const auto* next : inner_cur->Successors(action)) {
              if (!inner_visited.contains(next)) {
                inner_stack.push(next);
                inner_visited.insert(next);
                found_unvisited_successor_inner = true;
                break;
              }
            }
            if (found_unvisited_successor_inner) {
              break;
            }
          }
          if (found_unvisited_successor_inner) {
            continue;
          }
          inner_stack.pop();
        }
      }
    }
  }
  return true;
}