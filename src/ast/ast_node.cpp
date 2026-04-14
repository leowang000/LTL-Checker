#include "ast/ast_node.h"

#include <utility>

ASTNode::ASTNode(bool is_negated) : is_negated_(is_negated), id_() {}

bool ASTNode::is_negated() const { return is_negated_; }

void ASTNode::set_negated(bool is_negated) { is_negated_ = is_negated; }

void ASTNode::negate() { is_negated_ = !is_negated_; }

size_t ASTNode::id() const { return id_; }

void ASTNode::set_id(size_t id) { id_ = id; }

NextASTNode::NextASTNode(std::unique_ptr<ASTNode> child, bool is_negated)
    : ASTNode(is_negated), child_(std::move(child)) {}

const ASTNode* NextASTNode::child() const { return child_.get(); }
ASTNode* NextASTNode::child() { return child_.get(); }

AndASTNode::AndASTNode(std::unique_ptr<ASTNode> left,
                       std::unique_ptr<ASTNode> right, bool is_negated)
    : ASTNode(is_negated), left_(std::move(left)), right_(std::move(right)) {}

const ASTNode* AndASTNode::left() const { return left_.get(); }
ASTNode* AndASTNode::left() { return left_.get(); }
const ASTNode* AndASTNode::right() const { return right_.get(); }
ASTNode* AndASTNode::right() { return right_.get(); }

UntilASTNode::UntilASTNode(std::unique_ptr<ASTNode> left,
                           std::unique_ptr<ASTNode> right, bool is_negated)
    : ASTNode(is_negated), left_(std::move(left)), right_(std::move(right)) {}

const ASTNode* UntilASTNode::left() const { return left_.get(); }
ASTNode* UntilASTNode::left() { return left_.get(); }
const ASTNode* UntilASTNode::right() const { return right_.get(); }
ASTNode* UntilASTNode::right() { return right_.get(); }

AtomASTNode::AtomASTNode(std::string proposition, bool is_negated)
    : ASTNode(is_negated), proposition_(std::move(proposition)) {}

const std::string AtomASTNode::Proposition() const { return proposition_; }

TrueASTNode::TrueASTNode(bool is_negated) : ASTNode(is_negated) {}