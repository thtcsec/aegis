#pragma once
#include <string>
#include <unordered_map>
#include <unordered_set>

namespace aegis::security {

enum class TaintLevel { CLEAN, TAINTED, SANITIZED };

struct TaintInfo {
    TaintLevel level;
    std::string source;
    int line;
};

class TaintAnalyzer {
public:
    TaintAnalyzer();

    void markTainted(const std::string& var, const std::string& source, int line);
    void markSanitized(const std::string& var);
    bool isTainted(const std::string& var) const;
    TaintInfo getTaintInfo(const std::string& var) const;

    // Check for dangerous operations with tainted data
    bool checkSQLInjection(const std::string& query, const std::string& var);
    bool checkCommandInjection(const std::string& cmd, const std::string& var);
    bool checkPathTraversal(const std::string& path, const std::string& var);

private:
    std::unordered_map<std::string, TaintInfo> taint_map_;
    std::unordered_set<std::string> taint_sources_;
};

}  // namespace aegis::security
