#include <iostream>

#include "antlr4-runtime.h"
#include "ast/ast.h"
#include "ast/ast_builder.h"
#include "gnba.h"
#include "ltl_to_gnba_builder.h"
#include "persistence_checker.h"
#include "product_ts_constructor.h"
#include "ts.h"

int main() {
  std::ifstream ts_input_file("../benchmark/1.ts.in");
  std::ifstream ltl_input_file("../benchmark/1.ltl.in");
  auto [ts, atomic_propositions] = ReadTransitionSystemInput(ts_input_file);
  auto ltls = ReadLTLInputFile(ltl_input_file);
  for (auto &[initial_state, ast] : ltls) {
    ast.root()->Negate();
    auto gnba = LTLToGNBABuilder::Build(ast, atomic_propositions);
    auto nba = gnba.ToNBA();
    auto product_ts = ProductTSConstructor::Build(ts, nba, initial_state);
    std::cout << PersistenceChecker::Check(product_ts, nba) << std::endl;
  }
  return 0;
}