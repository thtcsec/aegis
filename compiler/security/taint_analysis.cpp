#include "taint_analysis.hpp"

namespace aegis::security {

TaintAnalyzer::TaintAnalyzer() {
    // Define taint sources
    taint_sources_ = {"input", "read", "recv", "getenv"};
}

void TaintAnalyzer::markTainted(const std::string& var, const std::string& source, int line) {
    taint_map_[var] = TaintInfo{TaintLevel::TAINTED, source, line};
}

void TaintAnalyzer::markSanitized(const std::string& var) {
    if (taint_map_.count(var)) {
        taint_map_[var].level = TaintLevel::SANITIZED;
    }
}

bool TaintAnalyzer::isTainted(const std::string& var) const {
    auto it = taint_map_.find(var);
    return it != taint_map_.end() && it->second.level == TaintLevel::TAINTED;
}

TaintInfo TaintAnalyzer::getTaintInfo(const std::string& var) const {
    auto it = taint_map_.find(var);
    if (it != taint_map_.end()) {
        return it->second;
    }
    return TaintInfo{TaintLevel::CLEAN, "", 0};
}

bool TaintAnalyzer::checkSQLInjection(const std::string& query, const std::string& var) {
    return isTainted(var);
}

bool TaintAnalyzer::checkCommandInjection(const std::string& cmd, const std::string& var) {
    return isTainted(var);
}

bool TaintAnalyzer::checkPathTraversal(const std::string& path, const std::string& var) {
    return isTainted(var);
}

}  // namespace aegis::security
