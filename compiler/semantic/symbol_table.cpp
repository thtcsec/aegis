#include "symbol_table.hpp"

namespace aegis {

SymbolTable::SymbolTable() {}

void SymbolTable::insert(const std::string& name, const Symbol& symbol) {
    symbols_[name] = symbol;
}

bool SymbolTable::lookup(const std::string& name) const {
    return symbols_.find(name) != symbols_.end();
}

}  // namespace aegis
