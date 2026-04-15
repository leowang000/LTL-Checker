#include <iostream>

#include "antlr4-runtime.h"
#include "ast/ast.h"
#include "ast/ast_builder.h"

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon
// src="AllIcons.Actions.Execute"/> icon in the gutter.
int main() {
  // TIP Press <shortcut actionId="RenameElement"/> when your caret is at the
  // <b>lang</b> variable name to see how CLion can help you rename it.
  std::string input;
  getline(std::cin, input);
  AST ast = ASTBuilder::Build(input);
  std::cout << ast.DebugString() << std::endl;
  return 0;
  // TIP See CLion help at <a
  // href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
  // Also, you can try interactive lessons for CLion by selecting 'Help | Learn
  // IDE Features' from the main menu.
}