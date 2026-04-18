#include <iostream>

#include "antlr4-runtime.h"
#include "ast/ast.h"
#include "ast/ast_builder.h"
#include "gnba.h"
#include "ltl_to_gnba_builder.h"
#include "persistence_checker.h"
#include "product_ts_constructor.h"
#include "ts.h"

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " <TS.txt> <benchmark.txt>" << std::endl;
    return 1;
  }
  std::string ts_file = argv[1];
  std::string ltl_file = argv[2];

  std::ifstream ts_input_file(ts_file);
  std::ifstream ltl_input_file(ltl_file);

  if (!ts_input_file.is_open()) {
    std::cerr << "Failed to open TS input file: " << ts_file << std::endl;
    return 1;
  }
  if (!ltl_input_file.is_open()) {
    std::cerr << "Failed to open LTL input file: " << ltl_file << std::endl;
    return 1;
  }

  auto [ts, atomic_propositions] = ReadTransitionSystemInput(ts_input_file);
  auto ltls = ReadLTLInputFile(ltl_input_file);
  for (auto& [initial_state, ast] : ltls) {
    ast.root()->Negate();
    auto gnba = LTLToGNBABuilder::Build(ast, atomic_propositions);
    auto nba = gnba.ToNBA();
    auto product_ts = ProductTSConstructor::Build(ts, nba, initial_state);
    std::cout << PersistenceChecker::Check(product_ts, nba) << std::endl;
  }
  return 0;
}