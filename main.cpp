#include <iostream>

#include "antlr4-runtime.h"
#include "ast/ast.h"
#include "ast/ast_builder.h"
#include "gnba.h"
#include "product.h"
#include "ts.h"

int main() {
  std::fstream ts_input_file("../testcases/1.tsbenchmark/1.ts.in.in");
  auto ts = ReadTransitionSystem(ts_input_file);
  GNBA<size_t> gnba;
  return 0;
}