#include "ast/ast_node.h"

#include <fmt/core.h>

#include <utility>

ASTNode::ASTNode(bool is_negated, ASTNode* parent)
    : parent_(parent), is_negated_(is_negated), id_() {}

ASTNode* ASTNode::parent() const { return parent_; }
void ASTNode::set_parent(ASTNode* parent) { parent_ = parent; }
bool ASTNode::is_negated() const { return is_negated_; }
void ASTNode::set_negated(bool is_negated) { is_negated_ = is_negated; }
void ASTNode::Negate() { is_negated_ = !is_negated_; }
size_t ASTNode::id() const { return id_; }
void ASTNode::set_id(size_t id) { id_ = id; }

std::string ASTNode::NegatedString() const {
  return is_negated_ ? " [Negated]" : "";
}

NextASTNode::NextASTNode(std::unique_ptr<ASTNode> child, bool is_negated)
    : ASTNode(is_negated), child_(std::move(child)) {
  child_->set_parent(this);
}

std::string NextASTNode::DebugString(size_t indent) const {
  return fmt::format("{}Next{}\n{}", std::string(indent, ' '), NegatedString(),
                     child_->DebugString(indent + 2));
}

const ASTNode* NextASTNode::child() const { return child_.get(); }
ASTNode* NextASTNode::child() { return child_.get(); }

AndASTNode::AndASTNode(std::unique_ptr<ASTNode> left,
                       std::unique_ptr<ASTNode> right, bool is_negated)
    : ASTNode(is_negated), left_(std::move(left)), right_(std::move(right)) {
  left_->set_parent(this);
  right_->set_parent(this);
}

std::string AndASTNode::DebugString(size_t indent) const {
  return fmt::format("{}And{}\n{}\n{}", std::string(indent, ' '),
                     NegatedString(), left_->DebugString(indent + 2),
                     right_->DebugString(indent + 2));
}

const ASTNode* AndASTNode::left() const { return left_.get(); }
ASTNode* AndASTNode::left() { return left_.get(); }
const ASTNode* AndASTNode::right() const { return right_.get(); }
ASTNode* AndASTNode::right() { return right_.get(); }

UntilASTNode::UntilASTNode(std::unique_ptr<ASTNode> left,
                           std::unique_ptr<ASTNode> right, bool is_negated)
    : ASTNode(is_negated), left_(std::move(left)), right_(std::move(right)) {
  left_->set_parent(this);
  right_->set_parent(this);
}

std::string UntilASTNode::DebugString(size_t indent) const {
  return fmt::format("{}Until{}\n{}\n{}", std::string(indent, ' '),
                     NegatedString(), left_->DebugString(indent + 2),
                     right_->DebugString(indent + 2));
}

const ASTNode* UntilASTNode::left() const { return left_.get(); }
ASTNode* UntilASTNode::left() { return left_.get(); }
const ASTNode* UntilASTNode::right() const { return right_.get(); }
ASTNode* UntilASTNode::right() { return right_.get(); }

AtomASTNode::AtomASTNode(std::string proposition, bool is_negated)
    : ASTNode(is_negated), proposition_(std::move(proposition)) {}

std::string AtomASTNode::DebugString(size_t indent) const {
  return fmt::format("{}Atom({}){}", std::string(indent, ' '), proposition_,
                     NegatedString());
}

const std::string AtomASTNode::Proposition() const { return proposition_; }

TrueASTNode::TrueASTNode(bool is_negated) : ASTNode(is_negated) {}

std::string TrueASTNode::DebugString(size_t indent) const {
  return fmt::format("{}True{}", std::string(indent, ' '), NegatedString());
}