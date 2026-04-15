#ifndef LTL_CHECKER_AST_BUILDER_H
#define LTL_CHECKER_AST_BUILDER_H

#include <memory>

#include "LTLParser.h"
#include "ast/ast.h"
#include "ast/ast_node.h"

class ASTBuilder {
 public:
  ASTBuilder() = default;
  ~ASTBuilder() = default;

  static AST Build(std::string_view input);

 private:
  static AST Build(LTLParser::FormulaContext* root);
  static std::unique_ptr<ASTNode> VisitNode(LTLParser::FormulaContext* ctx);
  static std::unique_ptr<ASTNode> VisitParen(LTLParser::ParenContext* ctx);
  static std::unique_ptr<ASTNode> VisitNot(LTLParser::NotContext* ctx);
  static std::unique_ptr<ASTNode> VisitNext(LTLParser::NextContext* ctx);
  static std::unique_ptr<ASTNode> VisitAlways(LTLParser::AlwaysContext* ctx);
  static std::unique_ptr<ASTNode> VisitEventually(LTLParser::EventuallyContext* ctx);
  static std::unique_ptr<ASTNode> VisitAnd(LTLParser::AndContext* ctx);
  static std::unique_ptr<ASTNode> VisitOr(LTLParser::OrContext* ctx);
  static std::unique_ptr<ASTNode> VisitImplies(LTLParser::ImpliesContext* ctx);
  static std::unique_ptr<ASTNode> VisitUntil(LTLParser::UntilContext* ctx);
  static std::unique_ptr<ASTNode> VisitTrueLit(LTLParser::TrueLitContext* ctx);
  static std::unique_ptr<ASTNode> VisitFalseLit(LTLParser::FalseLitContext* ctx);
  static std::unique_ptr<ASTNode> VisitAtomExpr(LTLParser::AtomExprContext* ctx);
};

#endif  // LTL_CHECKER_AST_BUILDER_H
