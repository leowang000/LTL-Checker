#ifndef LTL_CHECKER_AST_NODE_H
#define LTL_CHECKER_AST_NODE_H

#include <memory>

class ASTNode {
 public:
  explicit ASTNode(bool is_negated = false);
  virtual ~ASTNode() = default;

  bool is_negated() const;
  void set_negated(bool is_negated);
  void negate();
  size_t id() const;
  void set_id(size_t id);

 private:
  bool is_negated_;
  size_t id_{};
};

class NextASTNode : public ASTNode {
 public:
  explicit NextASTNode(std::unique_ptr<ASTNode> child, bool is_negated = false);
  ~NextASTNode() override = default;

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

  const std::string Proposition() const;

 private:
  std::string proposition_;
};

class TrueASTNode : public ASTNode {
 public:
  explicit TrueASTNode(bool is_negated = false);
  ~TrueASTNode() override = default;
};

#endif  // LTL_CHECKER_AST_NODE_H
