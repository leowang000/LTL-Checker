
// Generated from LTL.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "LTLParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by LTLParser.
 */
class  LTLVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by LTLParser.
   */
    virtual std::any visitNext(LTLParser::NextContext *context) = 0;

    virtual std::any visitAlways(LTLParser::AlwaysContext *context) = 0;

    virtual std::any visitParen(LTLParser::ParenContext *context) = 0;

    virtual std::any visitNot(LTLParser::NotContext *context) = 0;

    virtual std::any visitTrueLit(LTLParser::TrueLitContext *context) = 0;

    virtual std::any visitOr(LTLParser::OrContext *context) = 0;

    virtual std::any visitAnd(LTLParser::AndContext *context) = 0;

    virtual std::any visitFalseLit(LTLParser::FalseLitContext *context) = 0;

    virtual std::any visitAtomExpr(LTLParser::AtomExprContext *context) = 0;

    virtual std::any visitEventually(LTLParser::EventuallyContext *context) = 0;

    virtual std::any visitUntil(LTLParser::UntilContext *context) = 0;

    virtual std::any visitImplies(LTLParser::ImpliesContext *context) = 0;


};

