#include "ts.h"

#include <sstream>

// Step 1: Parser - transition system reading
// Reads the transition system from the input stream according to the specified format.
std::pair<TransitionSystem<size_t, size_t, std::string>, std::vector<std::string>>
ReadTransitionSystemInput(std::istream& input) {
  TransitionSystem<size_t, size_t, std::string> ts;
  std::vector<std::string> atomic_propositions;
  std::string line;
  size_t num_states, num_transitions;
  {
    std::getline(input, line);
    std::istringstream iss(line);
    iss >> num_states >> num_transitions;
    ts.nodes().reserve(num_states);
    for (size_t i = 0; i < num_states; ++i) {
      ts.nodes().emplace_back(i);
    }
  }
  {
    std::getline(input, line);
    std::istringstream iss(line);
    size_t initial_state;
    while (iss >> initial_state) {
      ts.initial_states().push_back(&ts.nodes()[initial_state]);
    }
  }
  {
    std::getline(input, line);
    std::istringstream iss(line);
    size_t action;
    while (iss >> action) {
      ts.actions().push_back(action);
    }
  }
  {
    std::getline(input, line);
    std::istringstream iss(line);
    std::string ap;
    while (iss >> ap) {
      atomic_propositions.push_back(ap);
    }
  }
  {
    for (size_t i = 0; i < num_transitions; ++i) {
      getline(input, line);
      std::istringstream iss(line);
      size_t from, to, action;
      iss >> from >> action >> to;
      ts.nodes()[from].Successors(action).insert(&ts.nodes()[to]);
    }
  }
  {
    for (size_t i = 0; i < num_states; ++i) {
      getline(input, line);
      std::istringstream iss(line);
      size_t ap_id;
      while (iss >> ap_id) {
        ts.nodes()[i].label().insert(atomic_propositions[ap_id]);
      }
    }
  }
  return {std::move(ts), std::move(atomic_propositions)};
}