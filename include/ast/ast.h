#ifndef LTL_CHECKER_AST_H
#define LTL_CHECKER_AST_H

#include <memory>
#include <vector>

#include "ast/ast_node.h"

class AST {
 public:
  explicit AST(std::unique_ptr<ASTNode> root);
  ~AST() = default;
  AST(AST&&) noexcept = default;
  AST& operator=(AST&&) noexcept = default;
  AST(const AST&) = delete;
  AST& operator=(const AST&) = delete;

  const ASTNode* root() const;
  ASTNode* root();
  const std::vector<ASTNode*>& id_to_node() const;
  std::vector<ASTNode*>& id_to_node();
  std::string DebugString(size_t indent = 0) const;

 private:
  std::unique_ptr<ASTNode> root_;
  std::vector<ASTNode*> id_to_node_;

  void AssignIdsAndBuildMap(ASTNode* node);
};

#endif  // LTL_CHECKER_AST_H
