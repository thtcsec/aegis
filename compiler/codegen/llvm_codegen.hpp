#pragma once
#include "../ast/ast_nodes.hpp"

namespace aegis {

class LLVMCodeGen {
public:
    LLVMCodeGen();
    void generate(ASTNode* node);
};

}  // namespace aegis
