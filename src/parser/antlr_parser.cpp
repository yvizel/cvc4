/*********************                                           -*- C++ -*-  */
/** antlr_parser.cpp
 ** Original author: dejan
 ** Major contributors: none
 ** Minor contributors (to current version): cconway, mdeters
 ** This file is part of the CVC4 prototype.
 ** Copyright (c) 2009 The Analysis of Computer Systems Group (ACSys)
 ** Courant Institute of Mathematical Sciences
 ** New York University
 ** See the file COPYING in the top-level source directory for licensing
 ** information.
 **
 ** [[ Add file-specific comments here ]]
 **/

/*
 * antlr_parser.cpp
 *
 *  Created on: Nov 30, 2009
 *      Author: dejan
 */

#include <iostream>

#include "antlr_parser.h"
#include "util/output.h"
#include "util/Assert.h"

using namespace std;
using namespace CVC4;
using namespace CVC4::parser;

namespace CVC4 {
namespace parser {

AntlrParser::AntlrParser(const antlr::ParserSharedInputState& state, int k) :
  antlr::LLkParser(state, k) {
}

AntlrParser::AntlrParser(antlr::TokenBuffer& tokenBuf, int k) :
  antlr::LLkParser(tokenBuf, k) {
}

AntlrParser::AntlrParser(antlr::TokenStream& lexer, int k) :
  antlr::LLkParser(lexer, k) {
}

Expr AntlrParser::getVariable(std::string var_name) {
  Expr e = d_varSymbolTable.getObject(var_name);
  Debug("parser") << "getvar " << var_name << " gives " << e << endl;
  return e;
}

Expr AntlrParser::getTrueExpr() const {
  return d_exprManager->mkExpr(TRUE);
}

Expr AntlrParser::getFalseExpr() const {
  return d_exprManager->mkExpr(FALSE);
}

Expr AntlrParser::mkExpr(Kind kind, const Expr& child) {
  return d_exprManager->mkExpr(kind, child);
}

Expr AntlrParser::mkExpr(Kind kind, const Expr& child_1, const Expr& child_2) {
  return d_exprManager->mkExpr(kind, child_1, child_2);
}

Expr AntlrParser::mkExpr(Kind kind, const Expr& child_1, const Expr& child_2,
                         const Expr& child_3) {
  return d_exprManager->mkExpr(kind, child_1, child_2, child_3);
}

Expr AntlrParser::mkExpr(Kind kind, const std::vector<Expr>& children) {
  return d_exprManager->mkExpr(kind, children);
}

void AntlrParser::newPredicate(std::string name,
                               const std::vector<std::string>& sorts) {
  if(sorts.size() == 0) {
    d_varSymbolTable.bindName(name, d_exprManager->mkVar());
  } else {
    Unhandled("Non unary predicate not supported yet!");
  }
}

void AntlrParser::newPredicates(const std::vector<std::string>& names,
                                const std::vector<std::string>& sorts) {
  for(unsigned i = 0; i < names.size(); ++i) {
    newPredicate(names[i], sorts);
  }
}

void AntlrParser::setExpressionManager(ExprManager* em) {
  d_exprManager = em;
}

bool AntlrParser::isDeclared(string name, SymbolType type) {
  switch(type) {
  case SYM_VARIABLE:
    return d_varSymbolTable.isBound(name);
  default:
    Unhandled("Unhandled symbol type!");
  }
}

void AntlrParser::rethrow(antlr::SemanticException& e, string new_message)
    throw (antlr::SemanticException) {
  throw antlr::SemanticException(new_message, getFilename(),
                                 LT(1).get()->getLine(),
                                 LT(1).get()->getColumn());
}

bool AntlrParser::checkDeclaration(string varName, DeclarationCheck check) {
  switch(check) {
  case CHECK_DECLARED:
    return isDeclared(varName, SYM_VARIABLE);
  case CHECK_UNDECLARED:
    return !isDeclared(varName, SYM_VARIABLE);
  case CHECK_NONE:
    return true;
  default:
    Unhandled("Unknown check type!");
  }
}

}/* CVC4::parser namespace */
}/* CVC4 namespace */
