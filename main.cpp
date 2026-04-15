#include <iostream>

#include "antlr4-runtime.h"
#include "ast/ast.h"
#include "ast/ast_builder.h"
#include "ts.h"

int main() {
  std::fstream ts_input_file("../testcases/TS.txt");
  TransitionSystem<size_t, size_t> ts = ReadTransitionSystem(ts_input_file);
  return 0;
}