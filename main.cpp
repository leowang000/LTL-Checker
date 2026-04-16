#include <iostream>

#include "antlr4-runtime.h"
#include "ast/ast.h"
#include "ast/ast_builder.h"
#include "gnba.h"
#include "persistence_checker.h"
#include "product_ts_constructor.h"
#include "ts.h"

int main() {
  std::fstream ts_input_file("../testcases/1.tsbenchmark/1.ts.in.in");
  std::vector<std::string> atomic_propositions;
  auto ts = ReadTransitionSystem(ts_input_file, atomic_propositions);
  return 0;
}