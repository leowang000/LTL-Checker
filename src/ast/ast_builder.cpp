#include "ast/ast_builder.h"

#include <sstream>
#include <utility>

#include "LTLLexer.h"
#include "LTLParser.h"

AST ASTBuilder::Build(std::string_view input) {
  antlr4::ANTLRInputStream stream(input);
  LTLLexer lexer(&stream);
  antlr4::CommonTokenStream tokens(&lexer);
  LTLParser parser(&tokens);
  auto tree = parser.formula();
  return Build(tree);
}

AST ASTBuilder::Build(LTLParser::FormulaContext* root) { return AST(VisitNode(root)); }

std::unique_ptr<ASTNode> ASTBuilder::VisitNode(LTLParser::FormulaContext* ctx) {
  if (auto* paren_ctx = dynamic_cast<LTLParser::ParenContext*>(ctx)) {
    return VisitParen(paren_ctx);
  } else if (auto* not_ctx = dynamic_cast<LTLParser::NotContext*>(ctx)) {
    return VisitNot(not_ctx);
  } else if (auto* next_ctx = dynamic_cast<LTLParser::NextContext*>(ctx)) {
    return VisitNext(next_ctx);
  } else if (auto* always_ctx = dynamic_cast<LTLParser::AlwaysContext*>(ctx)) {
    return VisitAlways(always_ctx);
  } else if (auto* eventually_ctx = dynamic_cast<LTLParser::EventuallyContext*>(ctx)) {
    return VisitEventually(eventually_ctx);
  } else if (auto* and_ctx = dynamic_cast<LTLParser::AndContext*>(ctx)) {
    return VisitAnd(and_ctx);
  } else if (auto* or_ctx = dynamic_cast<LTLParser::OrContext*>(ctx)) {
    return VisitOr(or_ctx);
  } else if (auto* implies_ctx = dynamic_cast<LTLParser::ImpliesContext*>(ctx)) {
    return VisitImplies(implies_ctx);
  } else if (auto* until_ctx = dynamic_cast<LTLParser::UntilContext*>(ctx)) {
    return VisitUntil(until_ctx);
  } else if (auto* true_ctx = dynamic_cast<LTLParser::TrueLitContext*>(ctx)) {
    return VisitTrueLit(true_ctx);
  } else if (auto* false_ctx = dynamic_cast<LTLParser::FalseLitContext*>(ctx)) {
    return VisitFalseLit(false_ctx);
  } else if (auto* atom_ctx = dynamic_cast<LTLParser::AtomExprContext*>(ctx)) {
    return VisitAtomExpr(atom_ctx);
  }
  return nullptr;
}

std::unique_ptr<ASTNode> ASTBuilder::VisitParen(LTLParser::ParenContext* ctx) {
  return VisitNode(ctx->formula());
}

std::unique_ptr<ASTNode> ASTBuilder::VisitNot(LTLParser::NotContext* ctx) {
  auto child = VisitNode(ctx->formula());
  if (child) {
    child->Negate();
  }
  return child;
}

std::unique_ptr<ASTNode> ASTBuilder::VisitNext(LTLParser::NextContext* ctx) {
  return std::make_unique<NextASTNode>(VisitNode(ctx->formula()));
}

std::unique_ptr<ASTNode> ASTBuilder::VisitAlways(LTLParser::AlwaysContext* ctx) {
  auto phi = VisitNode(ctx->formula());
  if (phi) {
    phi->Negate();
  }
  auto until_node = std::make_unique<UntilASTNode>(std::make_unique<TrueASTNode>(), std::move(phi));
  until_node->Negate();
  return until_node;
}

std::unique_ptr<ASTNode> ASTBuilder::VisitEventually(LTLParser::EventuallyContext* ctx) {
  return std::make_unique<UntilASTNode>(std::make_unique<TrueASTNode>(), VisitNode(ctx->formula()));
}

std::unique_ptr<ASTNode> ASTBuilder::VisitAnd(LTLParser::AndContext* ctx) {
  return std::make_unique<AndASTNode>(VisitNode(ctx->formula(0)), VisitNode(ctx->formula(1)));
}

std::unique_ptr<ASTNode> ASTBuilder::VisitOr(LTLParser::OrContext* ctx) {
  auto left = VisitNode(ctx->formula(0));
  if (left) {
    left->Negate();
  }
  auto right = VisitNode(ctx->formula(1));
  if (right) {
    right->Negate();
  }
  auto and_node = std::make_unique<AndASTNode>(std::move(left), std::move(right));
  and_node->Negate();
  return and_node;
}

std::unique_ptr<ASTNode> ASTBuilder::VisitImplies(LTLParser::ImpliesContext* ctx) {
  auto left = VisitNode(ctx->formula(0));
  auto right = VisitNode(ctx->formula(1));
  if (right) {
    right->Negate();
  }
  auto and_node = std::make_unique<AndASTNode>(std::move(left), std::move(right));
  and_node->Negate();
  return and_node;
}

std::unique_ptr<ASTNode> ASTBuilder::VisitUntil(LTLParser::UntilContext* ctx) {
  return std::make_unique<UntilASTNode>(VisitNode(ctx->formula(0)), VisitNode(ctx->formula(1)));
}

std::unique_ptr<ASTNode> ASTBuilder::VisitTrueLit(LTLParser::TrueLitContext* ctx) {
  return std::make_unique<TrueASTNode>();
}

std::unique_ptr<ASTNode> ASTBuilder::VisitFalseLit(LTLParser::FalseLitContext* ctx) {
  auto true_node = std::make_unique<TrueASTNode>();
  true_node->Negate();
  return true_node;
}

std::unique_ptr<ASTNode> ASTBuilder::VisitAtomExpr(LTLParser::AtomExprContext* ctx) {
  return std::make_unique<AtomASTNode>(ctx->ATOM()->getText());
}

std::vector<std::pair<int, AST>> ReadLTLInputFile(std::istream& input) {
  std::vector<std::pair<int, AST>> ltls;
  int num_all_initial_states, num_specified_initial_states;
  input >> num_all_initial_states >> num_specified_initial_states;
  std::string line;
  getline(input, line);
  for (int i = 0; i < num_all_initial_states; i++) {
    getline(input, line);
    ltls.emplace_back(-1, ASTBuilder::Build(line));
  }
  for (int i = 0; i < num_specified_initial_states; i++) {
    getline(input, line);
    std::istringstream iss(line);
    int initial_state;
    std::string ltl;
    iss >> initial_state;
    getline(iss, ltl);
    ltls.emplace_back(initial_state, ASTBuilder::Build(ltl));
  }
  return ltls;
}