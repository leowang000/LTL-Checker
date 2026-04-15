#ifndef LTL_CHECKER_AST_NODE_H
#define LTL_CHECKER_AST_NODE_H

#include <memory>

class ASTNode {
 public:
  explicit ASTNode(bool is_negated = false);
  virtual ~ASTNode() = default;

  virtual std::string DebugString(size_t indent) const = 0;

  bool is_negated() const;
  void set_negated(bool is_negated);
  void Negate();
  size_t id() const;
  void set_id(size_t id);

 protected:
  std::string NegatedString() const;

 private:
  bool is_negated_;
  size_t id_{};
};

class NextASTNode : public ASTNode {
 public:
  explicit NextASTNode(std::unique_ptr<ASTNode> child, bool is_negated = false);
  ~NextASTNode() override = default;

  std::string DebugString(size_t indent) const override;

  const ASTNode* child() const;
  ASTNode* child();

 private:
  std::unique_ptr<ASTNode> child_;
};

class AndASTNode : public ASTNode {
 public:
  AndASTNode(std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right,
             bool is_negated = false);
  ~AndASTNode() override = default;

  std::string DebugString(size_t indent) const override;

  const ASTNode* left() const;
  ASTNode* left();
  const ASTNode* right() const;
  ASTNode* right();

 private:
  std::unique_ptr<ASTNode> left_;
  std::unique_ptr<ASTNode> right_;
};

class UntilASTNode : public ASTNode {
 public:
  UntilASTNode(std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right,
               bool is_negated = false);
  ~UntilASTNode() override = default;

  std::string DebugString(size_t indent) const override;

  const ASTNode* left() const;
  ASTNode* left();
  const ASTNode* right() const;
  ASTNode* right();

 private:
  std::unique_ptr<ASTNode> left_;
  std::unique_ptr<ASTNode> right_;
};

class AtomASTNode : public ASTNode {
 public:
  explicit AtomASTNode(std::string proposition, bool is_negated = false);
  ~AtomASTNode() override = default;

  std::string DebugString(size_t indent) const override;

  const std::string Proposition() const;

 private:
  std::string proposition_;
};

class TrueASTNode : public ASTNode {
 public:
  explicit TrueASTNode(bool is_negated = false);
  ~TrueASTNode() override = default;

  std::string DebugString(size_t indent) const override;
};

#endif  // LTL_CHECKER_AST_NODE_H
