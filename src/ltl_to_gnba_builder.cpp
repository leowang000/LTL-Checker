#include "ltl_to_gnba_builder.h"

#include <unordered_map>
#include <vector>

GNBA<boost::dynamic_bitset<>> LTLToGNBABuilder::Build(
    const AST& ast, const std::vector<std::string>& atomic_propositions) {
  std::vector<std::vector<size_t>> atom_ids(atomic_propositions.size());
  std::unordered_map<std::string, size_t> ap_id_map;
  for (size_t i = 0; i < atomic_propositions.size(); ++i) {
    ap_id_map[atomic_propositions[i]] = i;
  }
  for (auto ast_node : ast.id_to_node()) {
    if (auto* atom_node = dynamic_cast<const AtomASTNode*>(ast_node)) {
      atom_ids[ap_id_map[atom_node->proposition()]].push_back(atom_node->id());
    }
  }

  std::unordered_map<boost::dynamic_bitset<>, std::vector<boost::dynamic_bitset<>>>
      elementary_sets_map;
  for (size_t i = 0; i < (1 << atomic_propositions.size()); ++i) {
    boost::dynamic_bitset<> assignment(atomic_propositions.size(), i);
    std::vector<boost::dynamic_bitset<>> current_sets = {
        boost::dynamic_bitset<>(ast.id_to_node().size())};
    ComputeElementarySets(ast.root(), assignment, atom_ids, ap_id_map, current_sets);
    elementary_sets_map[assignment] = current_sets;
  }

  GNBA<boost::dynamic_bitset<>> gnba;

  // Step 1: Construct the nodes of the gnba.
  for (const auto& [assignment, sets] : elementary_sets_map) {
    for (const auto& set : sets) {
      typename GNBA<boost::dynamic_bitset<>>::Node node(set);
      for (size_t i = 0; i < atomic_propositions.size(); ++i) {
        if (assignment[i]) {
          node.label().insert(atomic_propositions[i]);
        }
      }
      gnba.nodes().push_back(std::move(node));
    }
  }

  // Step 2: For each node, construct its successors.
  for (auto& current_gnba_node : gnba.nodes()) {
    const auto& current_set = current_gnba_node.state();
    boost::dynamic_bitset<> required_next_set(ast.id_to_node().size());
    boost::dynamic_bitset<> mask(ast.id_to_node().size());

    for (const auto* ast_node : ast.id_to_node()) {
      if (auto* next_node = dynamic_cast<const NextASTNode*>(ast_node)) {
        bool current_val = current_set[next_node->id()];
        size_t next_child_id = next_node->child()->id();
        mask[next_child_id] = true;
        required_next_set[next_child_id] =
            next_node->child()->is_negated() ? !current_val : current_val;
      } else if (auto* until_node = dynamic_cast<const UntilASTNode*>(ast_node)) {
        bool current_u = current_set[until_node->id()];
        bool current_left = current_set[until_node->left()->id()];
        if (until_node->left()->is_negated()) {
          current_left = !current_left;
        }
        bool current_right = current_set[until_node->right()->id()];
        if (until_node->right()->is_negated()) {
          current_right = !current_right;
        }

        if (current_u && !current_right) {
          mask[until_node->id()] = true;
          required_next_set[until_node->id()] = true;
        } else if (!current_u && current_left) {
          mask[until_node->id()] = true;
          required_next_set[until_node->id()] = false;
        }
      }
    }

    for (auto& next_gnba_node : gnba.nodes()) {
      if ((next_gnba_node.state() & mask) == required_next_set) {
        current_gnba_node.successors().insert(&next_gnba_node);
      }
    }
  }

  // Step 3: Construct the initial sets.
  for (const auto& gnba_node : gnba.nodes()) {
    if (gnba_node.state()[ast.root()->id()] == !ast.root()->is_negated()) {
      gnba.initial_states().push_back(&gnba_node);
    }
  }

  // Step 4: Each until node in ast corresponds to one acceptance set in acceptance_sets.
  for (const auto* ast_node : ast.id_to_node()) {
    if (auto* until_node = dynamic_cast<const UntilASTNode*>(ast_node)) {
      std::unordered_set<const typename GNBA<boost::dynamic_bitset<>>::Node*> acc_set;
      for (auto& gnba_node : gnba.nodes()) {
        const auto& state = gnba_node.state();
        bool u_val = state[until_node->id()];
        bool right_val = state[until_node->right()->id()];
        if (until_node->right()->is_negated()) {
          right_val = !right_val;
        }
        if (!u_val || right_val) {
          acc_set.insert(&gnba_node);
        }
      }
      gnba.acceptance_sets().push_back(std::move(acc_set));
    }
  }

  // Step 5: Call EnsureDefaultAcceptanceSet.
  gnba.EnsureDefaultAcceptanceSet();

  return gnba;
}

void LTLToGNBABuilder::ComputeElementarySets(
    const ASTNode* node, const boost::dynamic_bitset<>& atomic_assignment,
    const std::vector<std::vector<size_t>>& atom_ids,
    const std::unordered_map<std::string, size_t>& ap_id_map,
    std::vector<boost::dynamic_bitset<>>& current_sets) {
  // Evaluate children first for bottom-up computation
  if (auto* next_node = dynamic_cast<const NextASTNode*>(node)) {
    ComputeElementarySets(next_node->child(), atomic_assignment, atom_ids, ap_id_map, current_sets);
    std::vector<boost::dynamic_bitset<>> new_sets;
    for (const auto& set : current_sets) {
      boost::dynamic_bitset<> set_true = set;
      set_true[node->id()] = true;
      new_sets.push_back(set_true);

      boost::dynamic_bitset<> set_false = set;
      set_false[node->id()] = false;
      new_sets.push_back(set_false);
    }
    current_sets = std::move(new_sets);
  } else if (auto* and_node = dynamic_cast<const AndASTNode*>(node)) {
    ComputeElementarySets(and_node->left(), atomic_assignment, atom_ids, ap_id_map, current_sets);
    ComputeElementarySets(and_node->right(), atomic_assignment, atom_ids, ap_id_map, current_sets);
    for (auto& set : current_sets) {
      bool left_val = set[and_node->left()->id()];
      if (and_node->left()->is_negated()) {
        left_val = !left_val;
      }
      bool right_val = set[and_node->right()->id()];
      if (and_node->right()->is_negated()) {
        right_val = !right_val;
      }
      set[node->id()] = (left_val && right_val);
    }
  } else if (auto* until_node = dynamic_cast<const UntilASTNode*>(node)) {
    ComputeElementarySets(until_node->left(), atomic_assignment, atom_ids, ap_id_map, current_sets);
    ComputeElementarySets(until_node->right(), atomic_assignment, atom_ids, ap_id_map,
                          current_sets);
    std::vector<boost::dynamic_bitset<>> new_sets;
    for (const auto& set : current_sets) {
      bool left_val = set[until_node->left()->id()];
      if (until_node->left()->is_negated()) {
        left_val = !left_val;
      }
      bool right_val = set[until_node->right()->id()];
      if (until_node->right()->is_negated()) {
        right_val = !right_val;
      }
      if (right_val) {
        boost::dynamic_bitset<> s = set;
        s[node->id()] = true;
        new_sets.push_back(s);
      } else if (!left_val) {
        boost::dynamic_bitset<> s = set;
        s[node->id()] = false;
        new_sets.push_back(s);
      } else {
        boost::dynamic_bitset<> s_true = set;
        s_true[node->id()] = true;
        new_sets.push_back(s_true);
        boost::dynamic_bitset<> s_false = set;
        s_false[node->id()] = false;
        new_sets.push_back(s_false);
      }
    }
    current_sets = std::move(new_sets);
  } else if (auto* true_node = dynamic_cast<const TrueASTNode*>(node)) {
    for (auto& set : current_sets) {
      set[node->id()] = true;
    }
  } else if (auto* atom_node = dynamic_cast<const AtomASTNode*>(node)) {
    for (auto& set : current_sets) {
      set[node->id()] = atomic_assignment[ap_id_map.find(atom_node->proposition())->second];
    }
  }
}
