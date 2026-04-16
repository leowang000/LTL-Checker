#ifndef LTL_CHECKER_LTL_TO_GNBA_H
#define LTL_CHECKER_LTL_TO_GNBA_H

#include "ast/ast.h"
#include "boost/dynamic_bitset.hpp"
#include "gnba.h"

class LTLToGNBABuilder {
 public:
  LTLToGNBABuilder() = default;
  ~LTLToGNBABuilder() = default;

  static GNBA<boost::dynamic_bitset<>> Build(const AST& ast,
                                             const std::vector<std::string>& atomic_propositions);

 private:
  static void ComputeElementarySets(const ASTNode* node,
                                    const boost::dynamic_bitset<>& atomic_assignment,
                                    const std::vector<std::vector<size_t>>& atom_ids,
                                    const std::unordered_map<std::string, size_t>& ap_id_map,
                                    std::vector<boost::dynamic_bitset<>>& current_sets);
};

#endif  // LTL_CHECKER_LTL_TO_GNBA_H
