/*
 * Souffle - A Datalog Compiler
 * Copyright (c) 2013, Oracle and/or its affiliates. All rights reserved
 * Licensed under the Universal Permissive License v 1.0 as shown at:
 * - https://opensource.org/licenses/UPL
 * - <souffle root>/licenses/SOUFFLE-UPL.txt
 */

/************************************************************************
 *
 * @file SubsumptiveClause.h
 *
 * Defines the subsumptive clause class
 *
 ***********************************************************************/

#pragma once

#include "ast/Atom.h"
#include "ast/ExecutionPlan.h"
#include "ast/Literal.h"
#include "ast/Node.h"
#include "ast/Clause.h"
#include "parser/SrcLocation.h"
#include <iosfwd>
#include <vector>

namespace souffle::ast {

/**
 * @class Subsumptive Clause
 * @brief Intermediate representation of a subsumptive clause
 *
 * A subsumptive clause has the format
 * 
 *      R(...) <= R(...) :- body. 
 * 
 * Note that both atoms must refer to the same relation R. 
 *
 */
class SubsumptiveClause : public Clause {
public:
    SubsumptiveClause(Own<Atom> head, VecOwn<Literal> bodyLiterals, Own<ExecutionPlan> plan = {}, SrcLocation loc = {});

    /** Set subsumptive head */
    void setSubsumptiveHead(Own<Atom> h) {
        subsumptiveHead = h; 
    } 

    /** Obtain subsumptive head */
    Atom* getHead() const {
        return head.get();
    }

    void apply(const NodeMapper& map) override;

protected:
    void print(std::ostream& os) const override;

    NodeVec getChildren() const override;

private:
    bool equal(const Node& node) const override;

    Clause* cloning() const override;

private:
    /** Subsumptive kead */
    Own<Atom> subsumptiveHead;
};

}  // namespace souffle::ast
