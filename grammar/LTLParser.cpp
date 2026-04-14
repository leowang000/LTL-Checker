
// Generated from LTL.g4 by ANTLR 4.13.2


#include "LTLListener.h"
#include "LTLVisitor.h"

#include "LTLParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct LTLParserStaticData final {
  LTLParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  LTLParserStaticData(const LTLParserStaticData&) = delete;
  LTLParserStaticData(LTLParserStaticData&&) = delete;
  LTLParserStaticData& operator=(const LTLParserStaticData&) = delete;
  LTLParserStaticData& operator=(LTLParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag ltlParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<LTLParserStaticData> ltlParserStaticData = nullptr;

void ltlParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (ltlParserStaticData != nullptr) {
    return;
  }
#else
  assert(ltlParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<LTLParserStaticData>(
    std::vector<std::string>{
      "formula"
    },
    std::vector<std::string>{
      "", "'true'", "'false'", "", "'!'", "'/\\'", "'\\/'", "'->'", "'X'", 
      "'G'", "'F'", "'U'", "'('", "')'"
    },
    std::vector<std::string>{
      "", "TRUE", "FALSE", "ATOM", "NOT", "AND", "OR", "IMPLIES", "NEXT", 
      "ALWAYS", "EVENTUALLY", "UNTIL", "LPAREN", "RPAREN", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,14,38,2,0,7,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,
  	1,0,1,0,1,0,3,0,19,8,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
  	0,5,0,33,8,0,10,0,12,0,36,9,0,1,0,0,1,0,1,0,0,0,47,0,18,1,0,0,0,2,3,6,
  	0,-1,0,3,4,5,12,0,0,4,5,3,0,0,0,5,6,5,13,0,0,6,19,1,0,0,0,7,8,5,4,0,0,
  	8,19,3,0,0,11,9,10,5,8,0,0,10,19,3,0,0,10,11,12,5,9,0,0,12,19,3,0,0,9,
  	13,14,5,10,0,0,14,19,3,0,0,8,15,19,5,1,0,0,16,19,5,2,0,0,17,19,5,3,0,
  	0,18,2,1,0,0,0,18,7,1,0,0,0,18,9,1,0,0,0,18,11,1,0,0,0,18,13,1,0,0,0,
  	18,15,1,0,0,0,18,16,1,0,0,0,18,17,1,0,0,0,19,34,1,0,0,0,20,21,10,7,0,
  	0,21,22,5,5,0,0,22,33,3,0,0,8,23,24,10,6,0,0,24,25,5,6,0,0,25,33,3,0,
  	0,7,26,27,10,5,0,0,27,28,5,7,0,0,28,33,3,0,0,6,29,30,10,4,0,0,30,31,5,
  	11,0,0,31,33,3,0,0,5,32,20,1,0,0,0,32,23,1,0,0,0,32,26,1,0,0,0,32,29,
  	1,0,0,0,33,36,1,0,0,0,34,32,1,0,0,0,34,35,1,0,0,0,35,1,1,0,0,0,36,34,
  	1,0,0,0,3,18,32,34
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  ltlParserStaticData = std::move(staticData);
}

}

LTLParser::LTLParser(TokenStream *input) : LTLParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

LTLParser::LTLParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  LTLParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *ltlParserStaticData->atn, ltlParserStaticData->decisionToDFA, ltlParserStaticData->sharedContextCache, options);
}

LTLParser::~LTLParser() {
  delete _interpreter;
}

const atn::ATN& LTLParser::getATN() const {
  return *ltlParserStaticData->atn;
}

std::string LTLParser::getGrammarFileName() const {
  return "LTL.g4";
}

const std::vector<std::string>& LTLParser::getRuleNames() const {
  return ltlParserStaticData->ruleNames;
}

const dfa::Vocabulary& LTLParser::getVocabulary() const {
  return ltlParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView LTLParser::getSerializedATN() const {
  return ltlParserStaticData->serializedATN;
}


//----------------- FormulaContext ------------------------------------------------------------------

LTLParser::FormulaContext::FormulaContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t LTLParser::FormulaContext::getRuleIndex() const {
  return LTLParser::RuleFormula;
}

void LTLParser::FormulaContext::copyFrom(FormulaContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- NextContext ------------------------------------------------------------------

tree::TerminalNode* LTLParser::NextContext::NEXT() {
  return getToken(LTLParser::NEXT, 0);
}

LTLParser::FormulaContext* LTLParser::NextContext::formula() {
  return getRuleContext<LTLParser::FormulaContext>(0);
}

LTLParser::NextContext::NextContext(FormulaContext *ctx) { copyFrom(ctx); }

void LTLParser::NextContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNext(this);
}
void LTLParser::NextContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNext(this);
}

std::any LTLParser::NextContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LTLVisitor*>(visitor))
    return parserVisitor->visitNext(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AlwaysContext ------------------------------------------------------------------

tree::TerminalNode* LTLParser::AlwaysContext::ALWAYS() {
  return getToken(LTLParser::ALWAYS, 0);
}

LTLParser::FormulaContext* LTLParser::AlwaysContext::formula() {
  return getRuleContext<LTLParser::FormulaContext>(0);
}

LTLParser::AlwaysContext::AlwaysContext(FormulaContext *ctx) { copyFrom(ctx); }

void LTLParser::AlwaysContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAlways(this);
}
void LTLParser::AlwaysContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAlways(this);
}

std::any LTLParser::AlwaysContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LTLVisitor*>(visitor))
    return parserVisitor->visitAlways(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ParenContext ------------------------------------------------------------------

tree::TerminalNode* LTLParser::ParenContext::LPAREN() {
  return getToken(LTLParser::LPAREN, 0);
}

LTLParser::FormulaContext* LTLParser::ParenContext::formula() {
  return getRuleContext<LTLParser::FormulaContext>(0);
}

tree::TerminalNode* LTLParser::ParenContext::RPAREN() {
  return getToken(LTLParser::RPAREN, 0);
}

LTLParser::ParenContext::ParenContext(FormulaContext *ctx) { copyFrom(ctx); }

void LTLParser::ParenContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParen(this);
}
void LTLParser::ParenContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParen(this);
}

std::any LTLParser::ParenContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LTLVisitor*>(visitor))
    return parserVisitor->visitParen(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NotContext ------------------------------------------------------------------

tree::TerminalNode* LTLParser::NotContext::NOT() {
  return getToken(LTLParser::NOT, 0);
}

LTLParser::FormulaContext* LTLParser::NotContext::formula() {
  return getRuleContext<LTLParser::FormulaContext>(0);
}

LTLParser::NotContext::NotContext(FormulaContext *ctx) { copyFrom(ctx); }

void LTLParser::NotContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNot(this);
}
void LTLParser::NotContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNot(this);
}

std::any LTLParser::NotContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LTLVisitor*>(visitor))
    return parserVisitor->visitNot(this);
  else
    return visitor->visitChildren(this);
}
//----------------- TrueLitContext ------------------------------------------------------------------

tree::TerminalNode* LTLParser::TrueLitContext::TRUE() {
  return getToken(LTLParser::TRUE, 0);
}

LTLParser::TrueLitContext::TrueLitContext(FormulaContext *ctx) { copyFrom(ctx); }

void LTLParser::TrueLitContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTrueLit(this);
}
void LTLParser::TrueLitContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTrueLit(this);
}

std::any LTLParser::TrueLitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LTLVisitor*>(visitor))
    return parserVisitor->visitTrueLit(this);
  else
    return visitor->visitChildren(this);
}
//----------------- OrContext ------------------------------------------------------------------

std::vector<LTLParser::FormulaContext *> LTLParser::OrContext::formula() {
  return getRuleContexts<LTLParser::FormulaContext>();
}

LTLParser::FormulaContext* LTLParser::OrContext::formula(size_t i) {
  return getRuleContext<LTLParser::FormulaContext>(i);
}

tree::TerminalNode* LTLParser::OrContext::OR() {
  return getToken(LTLParser::OR, 0);
}

LTLParser::OrContext::OrContext(FormulaContext *ctx) { copyFrom(ctx); }

void LTLParser::OrContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOr(this);
}
void LTLParser::OrContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOr(this);
}

std::any LTLParser::OrContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LTLVisitor*>(visitor))
    return parserVisitor->visitOr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AndContext ------------------------------------------------------------------

std::vector<LTLParser::FormulaContext *> LTLParser::AndContext::formula() {
  return getRuleContexts<LTLParser::FormulaContext>();
}

LTLParser::FormulaContext* LTLParser::AndContext::formula(size_t i) {
  return getRuleContext<LTLParser::FormulaContext>(i);
}

tree::TerminalNode* LTLParser::AndContext::AND() {
  return getToken(LTLParser::AND, 0);
}

LTLParser::AndContext::AndContext(FormulaContext *ctx) { copyFrom(ctx); }

void LTLParser::AndContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAnd(this);
}
void LTLParser::AndContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAnd(this);
}

std::any LTLParser::AndContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LTLVisitor*>(visitor))
    return parserVisitor->visitAnd(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FalseLitContext ------------------------------------------------------------------

tree::TerminalNode* LTLParser::FalseLitContext::FALSE() {
  return getToken(LTLParser::FALSE, 0);
}

LTLParser::FalseLitContext::FalseLitContext(FormulaContext *ctx) { copyFrom(ctx); }

void LTLParser::FalseLitContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFalseLit(this);
}
void LTLParser::FalseLitContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFalseLit(this);
}

std::any LTLParser::FalseLitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LTLVisitor*>(visitor))
    return parserVisitor->visitFalseLit(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AtomExprContext ------------------------------------------------------------------

tree::TerminalNode* LTLParser::AtomExprContext::ATOM() {
  return getToken(LTLParser::ATOM, 0);
}

LTLParser::AtomExprContext::AtomExprContext(FormulaContext *ctx) { copyFrom(ctx); }

void LTLParser::AtomExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAtomExpr(this);
}
void LTLParser::AtomExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAtomExpr(this);
}

std::any LTLParser::AtomExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LTLVisitor*>(visitor))
    return parserVisitor->visitAtomExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- EventuallyContext ------------------------------------------------------------------

tree::TerminalNode* LTLParser::EventuallyContext::EVENTUALLY() {
  return getToken(LTLParser::EVENTUALLY, 0);
}

LTLParser::FormulaContext* LTLParser::EventuallyContext::formula() {
  return getRuleContext<LTLParser::FormulaContext>(0);
}

LTLParser::EventuallyContext::EventuallyContext(FormulaContext *ctx) { copyFrom(ctx); }

void LTLParser::EventuallyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEventually(this);
}
void LTLParser::EventuallyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEventually(this);
}

std::any LTLParser::EventuallyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LTLVisitor*>(visitor))
    return parserVisitor->visitEventually(this);
  else
    return visitor->visitChildren(this);
}
//----------------- UntilContext ------------------------------------------------------------------

std::vector<LTLParser::FormulaContext *> LTLParser::UntilContext::formula() {
  return getRuleContexts<LTLParser::FormulaContext>();
}

LTLParser::FormulaContext* LTLParser::UntilContext::formula(size_t i) {
  return getRuleContext<LTLParser::FormulaContext>(i);
}

tree::TerminalNode* LTLParser::UntilContext::UNTIL() {
  return getToken(LTLParser::UNTIL, 0);
}

LTLParser::UntilContext::UntilContext(FormulaContext *ctx) { copyFrom(ctx); }

void LTLParser::UntilContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUntil(this);
}
void LTLParser::UntilContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUntil(this);
}

std::any LTLParser::UntilContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LTLVisitor*>(visitor))
    return parserVisitor->visitUntil(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ImpliesContext ------------------------------------------------------------------

std::vector<LTLParser::FormulaContext *> LTLParser::ImpliesContext::formula() {
  return getRuleContexts<LTLParser::FormulaContext>();
}

LTLParser::FormulaContext* LTLParser::ImpliesContext::formula(size_t i) {
  return getRuleContext<LTLParser::FormulaContext>(i);
}

tree::TerminalNode* LTLParser::ImpliesContext::IMPLIES() {
  return getToken(LTLParser::IMPLIES, 0);
}

LTLParser::ImpliesContext::ImpliesContext(FormulaContext *ctx) { copyFrom(ctx); }

void LTLParser::ImpliesContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterImplies(this);
}
void LTLParser::ImpliesContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitImplies(this);
}

std::any LTLParser::ImpliesContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LTLVisitor*>(visitor))
    return parserVisitor->visitImplies(this);
  else
    return visitor->visitChildren(this);
}

LTLParser::FormulaContext* LTLParser::formula() {
   return formula(0);
}

LTLParser::FormulaContext* LTLParser::formula(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  LTLParser::FormulaContext *_localctx = _tracker.createInstance<FormulaContext>(_ctx, parentState);
  LTLParser::FormulaContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 0;
  enterRecursionRule(_localctx, 0, LTLParser::RuleFormula, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(18);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case LTLParser::LPAREN: {
        _localctx = _tracker.createInstance<ParenContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;

        setState(3);
        match(LTLParser::LPAREN);
        setState(4);
        formula(0);
        setState(5);
        match(LTLParser::RPAREN);
        break;
      }

      case LTLParser::NOT: {
        _localctx = _tracker.createInstance<NotContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(7);
        match(LTLParser::NOT);
        setState(8);
        formula(11);
        break;
      }

      case LTLParser::NEXT: {
        _localctx = _tracker.createInstance<NextContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(9);
        match(LTLParser::NEXT);
        setState(10);
        formula(10);
        break;
      }

      case LTLParser::ALWAYS: {
        _localctx = _tracker.createInstance<AlwaysContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(11);
        match(LTLParser::ALWAYS);
        setState(12);
        formula(9);
        break;
      }

      case LTLParser::EVENTUALLY: {
        _localctx = _tracker.createInstance<EventuallyContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(13);
        match(LTLParser::EVENTUALLY);
        setState(14);
        formula(8);
        break;
      }

      case LTLParser::TRUE: {
        _localctx = _tracker.createInstance<TrueLitContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(15);
        match(LTLParser::TRUE);
        break;
      }

      case LTLParser::FALSE: {
        _localctx = _tracker.createInstance<FalseLitContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(16);
        match(LTLParser::FALSE);
        break;
      }

      case LTLParser::ATOM: {
        _localctx = _tracker.createInstance<AtomExprContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(17);
        match(LTLParser::ATOM);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(34);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(32);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<AndContext>(_tracker.createInstance<FormulaContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleFormula);
          setState(20);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(21);
          match(LTLParser::AND);
          setState(22);
          formula(8);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<OrContext>(_tracker.createInstance<FormulaContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleFormula);
          setState(23);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(24);
          match(LTLParser::OR);
          setState(25);
          formula(7);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<ImpliesContext>(_tracker.createInstance<FormulaContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleFormula);
          setState(26);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(27);
          match(LTLParser::IMPLIES);
          setState(28);
          formula(6);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<UntilContext>(_tracker.createInstance<FormulaContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleFormula);
          setState(29);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(30);
          match(LTLParser::UNTIL);
          setState(31);
          formula(5);
          break;
        }

        default:
          break;
        } 
      }
      setState(36);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

bool LTLParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 0: return formulaSempred(antlrcpp::downCast<FormulaContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool LTLParser::formulaSempred(FormulaContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 7);
    case 1: return precpred(_ctx, 6);
    case 2: return precpred(_ctx, 5);
    case 3: return precpred(_ctx, 4);

  default:
    break;
  }
  return true;
}

void LTLParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  ltlParserInitialize();
#else
  ::antlr4::internal::call_once(ltlParserOnceFlag, ltlParserInitialize);
#endif
}
