
// Generated from LTL.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "LTLListener.h"


/**
 * This class provides an empty implementation of LTLListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  LTLBaseListener : public LTLListener {
public:

  virtual void enterNext(LTLParser::NextContext * /*ctx*/) override { }
  virtual void exitNext(LTLParser::NextContext * /*ctx*/) override { }

  virtual void enterAlways(LTLParser::AlwaysContext * /*ctx*/) override { }
  virtual void exitAlways(LTLParser::AlwaysContext * /*ctx*/) override { }

  virtual void enterParen(LTLParser::ParenContext * /*ctx*/) override { }
  virtual void exitParen(LTLParser::ParenContext * /*ctx*/) override { }

  virtual void enterNot(LTLParser::NotContext * /*ctx*/) override { }
  virtual void exitNot(LTLParser::NotContext * /*ctx*/) override { }

  virtual void enterTrueLit(LTLParser::TrueLitContext * /*ctx*/) override { }
  virtual void exitTrueLit(LTLParser::TrueLitContext * /*ctx*/) override { }

  virtual void enterOr(LTLParser::OrContext * /*ctx*/) override { }
  virtual void exitOr(LTLParser::OrContext * /*ctx*/) override { }

  virtual void enterAnd(LTLParser::AndContext * /*ctx*/) override { }
  virtual void exitAnd(LTLParser::AndContext * /*ctx*/) override { }

  virtual void enterFalseLit(LTLParser::FalseLitContext * /*ctx*/) override { }
  virtual void exitFalseLit(LTLParser::FalseLitContext * /*ctx*/) override { }

  virtual void enterAtomExpr(LTLParser::AtomExprContext * /*ctx*/) override { }
  virtual void exitAtomExpr(LTLParser::AtomExprContext * /*ctx*/) override { }

  virtual void enterEventually(LTLParser::EventuallyContext * /*ctx*/) override { }
  virtual void exitEventually(LTLParser::EventuallyContext * /*ctx*/) override { }

  virtual void enterUntil(LTLParser::UntilContext * /*ctx*/) override { }
  virtual void exitUntil(LTLParser::UntilContext * /*ctx*/) override { }

  virtual void enterImplies(LTLParser::ImpliesContext * /*ctx*/) override { }
  virtual void exitImplies(LTLParser::ImpliesContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

