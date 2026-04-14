
// Generated from LTL.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "LTLParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by LTLParser.
 */
class  LTLListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterNext(LTLParser::NextContext *ctx) = 0;
  virtual void exitNext(LTLParser::NextContext *ctx) = 0;

  virtual void enterAlways(LTLParser::AlwaysContext *ctx) = 0;
  virtual void exitAlways(LTLParser::AlwaysContext *ctx) = 0;

  virtual void enterParen(LTLParser::ParenContext *ctx) = 0;
  virtual void exitParen(LTLParser::ParenContext *ctx) = 0;

  virtual void enterNot(LTLParser::NotContext *ctx) = 0;
  virtual void exitNot(LTLParser::NotContext *ctx) = 0;

  virtual void enterTrueLit(LTLParser::TrueLitContext *ctx) = 0;
  virtual void exitTrueLit(LTLParser::TrueLitContext *ctx) = 0;

  virtual void enterOr(LTLParser::OrContext *ctx) = 0;
  virtual void exitOr(LTLParser::OrContext *ctx) = 0;

  virtual void enterAnd(LTLParser::AndContext *ctx) = 0;
  virtual void exitAnd(LTLParser::AndContext *ctx) = 0;

  virtual void enterFalseLit(LTLParser::FalseLitContext *ctx) = 0;
  virtual void exitFalseLit(LTLParser::FalseLitContext *ctx) = 0;

  virtual void enterAtomExpr(LTLParser::AtomExprContext *ctx) = 0;
  virtual void exitAtomExpr(LTLParser::AtomExprContext *ctx) = 0;

  virtual void enterEventually(LTLParser::EventuallyContext *ctx) = 0;
  virtual void exitEventually(LTLParser::EventuallyContext *ctx) = 0;

  virtual void enterUntil(LTLParser::UntilContext *ctx) = 0;
  virtual void exitUntil(LTLParser::UntilContext *ctx) = 0;

  virtual void enterImplies(LTLParser::ImpliesContext *ctx) = 0;
  virtual void exitImplies(LTLParser::ImpliesContext *ctx) = 0;


};

