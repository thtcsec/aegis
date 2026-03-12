#pragma once
#include <string>
#include <unordered_map>

namespace aegis {

struct Symbol {
    std::string name;
    std::string type;
    int line;
};

class SymbolTable {
public:
    SymbolTable();
    void insert(const std::string& name, const Symbol& symbol);
    bool lookup(const std::string& name) const;

private:
    std::unordered_map<std::string, Symbol> symbols_;
};

}  // namespace aegis
