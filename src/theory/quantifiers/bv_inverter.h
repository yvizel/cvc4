/*********************                                                        */
/*! \file bv_inverter.h
 ** \verbatim
 ** Top contributors (to current version):
 **   Andrew Reynolds
 ** This file is part of the CVC4 project.
 ** Copyright (c) 2009-2017 by the authors listed in the file AUTHORS
 ** in the top-level source directory) and their institutional affiliations.
 ** All rights reserved.  See the file COPYING in the top-level source
 ** directory for licensing information.\endverbatim
 **
 ** \brief inverse rules for bit-vector operators
 **/

#include "cvc4_private.h"

#ifndef __CVC4__BV_INVERTER_H
#define __CVC4__BV_INVERTER_H

#include <map>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "expr/node.h"

namespace CVC4 {
namespace theory {
namespace quantifiers {

/** BvInverterQuery
 *
 * This is a virtual class for queries
 * required by the BvInverter class.
 */
class BvInverterQuery
{
 public:
  BvInverterQuery() {}
  ~BvInverterQuery() {}
  /** returns the current model value of n */
  virtual Node getModelValue(Node n) = 0;
  /** returns a bound variable of type tn */
  virtual Node getBoundVariable(TypeNode tn) = 0;
};

// class for storing information about the solved status
class BvInverterStatus {
 public:
  BvInverterStatus() : d_status(0) {}
  ~BvInverterStatus() {}
  int d_status;
  // TODO : may not need this (conditions now appear explicitly in solved
  // forms) side conditions
  std::vector<Node> d_conds;
};

// inverter class
// TODO : move to theory/bv/ if generally useful?
class BvInverter {
 public:
  BvInverter() {}
  ~BvInverter() {}
  /** get dummy fresh variable of type tn, used as argument for sv */
  Node getSolveVariable(TypeNode tn);

  /** get inversion node
   *
   * This expects a condition cond where:
   *   (exists x. cond)
   * is a BV tautology where x is getSolveVariable( tn ).
   *
   * It returns a term of the form:
   *   (choice y. cond { x -> y })
   * where y is a bound variable and x is getSolveVariable( tn ).
   *
   * In some cases, we may return a term t
   * if cond implies an equality on the solve variable.
   * For example, if cond is x = t where x is
   * getSolveVariable( tn ), then we return t
   * instead of introducing the choice function.
   */
  Node getInversionNode(Node cond, TypeNode tn, BvInverterQuery* m);

  /** Get path to pv in lit, replace that occurrence by sv and all others by
   * pvs. If return value R is non-null, then : lit.path = pv R.path = sv
   *   R.path' = pvs for all lit.path' = pv, where path' != path
   */
  Node getPathToPv(Node lit, Node pv, Node sv, Node pvs,
                   std::vector<unsigned>& path);

  /** solve_bv_lit
   * solve for sv in lit, where lit.path = sv
   * status accumulates side conditions
   */
  Node solve_bv_lit(Node sv,
                    Node lit,
                    std::vector<unsigned>& path,
                    BvInverterQuery* m,
                    BvInverterStatus& status);

 private:
  /** dummy variables for each type */
  std::map<TypeNode, Node> d_solve_var;

  /** helper function for getPathToPv */
  Node getPathToPv(Node lit, Node pv, Node sv, std::vector<unsigned>& path,
                   std::unordered_set<TNode, TNodeHashFunction>& visited);

  // is operator k invertible?
  bool isInvertible(Kind k, unsigned index);
};

}  // namespace quantifiers
}  // namespace theory
}  // namespace CVC4

#endif /* __CVC4__BV_INVERTER_H */
