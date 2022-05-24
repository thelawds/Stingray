#include "InterpretationVisitor.h"

InterpretationVisitor::InterpretationVisitor()
    : context(std::make_unique<llvm::LLVMContext>()), builder(std::make_unique<llvm::IRBuilder<>>(*context)),
      module(std::make_unique<llvm::Module>("Test Stingray interpretation", *context)) { // todo: change module name

}

llvm::Value *InterpretationVisitor::stackPop() {
    auto *result = returnValues.top();
    returnValues.pop();
    return result;
}

void InterpretationVisitor::returnValue(llvm::Value *value) { returnValues.push(value); }

llvm::Value *InterpretationVisitor::visit(Visitable *tree) {
    tree->accept(this);
    return stackPop();
}


