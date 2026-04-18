#include "persistence_checker.h"

#include <stack>
#include <unordered_set>

#include "gnba.h"
#include "ts.h"

// Step 5: Nested depth-first search algorithm for checking persistence property (Algorithm 8, Page 211)
// Employs a nested DFS to find accepting cycles in the product automaton.
bool PersistenceChecker::Check(const ProductTSType& ts, const NBAType& nba) {
  const auto& acceptance_set = nba.acceptance_sets()[0];
  std::unordered_set<const ProductTSNode*> outer_visited;
  std::unordered_set<const ProductTSNode*> inner_visited;
  std::stack<const ProductTSNode*> outer_stack;
  for (const auto* ts_init : ts.initial_states()) {
    if (outer_visited.contains(ts_init)) {
      continue;
    }
    outer_stack.push(ts_init);
    outer_visited.insert(ts_init);
    while (!outer_stack.empty()) {
      const ProductTSNode* cur = outer_stack.top();
      bool found_unvisited_successor = false;
      for (auto action : ts.actions()) {
        for (const auto* next : cur->Successors(action)) {
          if (!outer_visited.contains(next)) {
            outer_stack.push(next);
            outer_visited.insert(next);
            found_unvisited_successor = true;
          }
        }
      }
      if (found_unvisited_successor) {
        continue;
      }
      outer_stack.pop();
      if (acceptance_set.contains(*cur->label().begin())) {
        if (CycleCheck(cur, ts, inner_visited)) {
          return false;
        }
      }
    }
  }
  return true;
}

bool PersistenceChecker::CycleCheck(const ProductTSNode* start, const ProductTSType& ts,
                                    std::unordered_set<const ProductTSNode*>& inner_visited) {
  std::stack<const ProductTSNode*> inner_stack;
  inner_stack.push(start);
  inner_visited.insert(start);
  while (!inner_stack.empty()) {
    const ProductTSNode* cur = inner_stack.top();
    for (auto action : ts.actions()) {
      if (cur->Successors(action).contains(start)) {
        return true;
      }
    }
    bool found_unvisited_successor = false;
    for (auto action : ts.actions()) {
      for (const auto* next : cur->Successors(action)) {
        if (!inner_visited.contains(next)) {
          inner_stack.push(next);
          inner_visited.insert(next);
          found_unvisited_successor = true;
        }
      }
    }
    if (found_unvisited_successor) {
      continue;
    }
    inner_stack.pop();
  }
  return false;
}