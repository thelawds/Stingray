#include "InterpretationVisitor.h"
#include <iostream>

void InterpretationVisitor::visitStatementAssignment(StatementAssignment *p) {
    stackFrame[p->ident_] = visit(p->value_);
    std::cout << p->ident_ << " equals " << stackFrame[p->ident_]->toString() << std::endl;
}

void InterpretationVisitor::visitStatementVarDecl(StatementVarDecl *p) {

}

