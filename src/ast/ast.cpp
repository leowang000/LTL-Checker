#include "ast/ast.h"

AST::AST(std::unique_ptr<ASTNode> root) : root_(std::move(root)) {
  if (root_) {
    AssignIdsAndBuildMap(root_.get());
  }
}

const ASTNode* AST::root() const { return root_.get(); }
ASTNode* AST::root() { return root_.get(); }
const std::vector<ASTNode*>& AST::id_to_node() const { return id_to_node_; }
std::vector<ASTNode*>& AST::id_to_node() { return id_to_node_; }

std::string AST::DebugString(size_t indent) const {
  return root_ ? root_->DebugString(indent) : "Empty AST";
}

void AST::AssignIdsAndBuildMap(ASTNode* node) {
  if (!node) {
    return;
  }

  size_t id = id_to_node_.size();
  node->set_id(id);
  id_to_node_.push_back(node);

  if (auto* next_node = dynamic_cast<NextASTNode*>(node)) {
    AssignIdsAndBuildMap(next_node->child());
  } else if (auto* and_node = dynamic_cast<AndASTNode*>(node)) {
    AssignIdsAndBuildMap(and_node->left());
    AssignIdsAndBuildMap(and_node->right());
  } else if (auto* until_node = dynamic_cast<UntilASTNode*>(node)) {
    AssignIdsAndBuildMap(until_node->left());
    AssignIdsAndBuildMap(until_node->right());
  }
}