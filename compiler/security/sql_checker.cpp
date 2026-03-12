#include "sql_checker.hpp"

#include <regex>

namespace aegis::security {

SQLChecker::SQLChecker() {}

bool SQLChecker::isParameterized(const std::string& query) const {
    // Check for parameterized query patterns (?, $1, :name)
    std::regex param_pattern(R"(\?|\$\d+|:\w+)");
    return std::regex_search(query, param_pattern);
}

bool SQLChecker::hasStringConcatenation(const std::string& query) const {
    // Detect string concatenation patterns
    return query.find("+") != std::string::npos || query.find("||") != std::string::npos;
}

SQLVulnerability SQLChecker::analyze(const std::string& query, bool usesTaintedInput) {
    SQLVulnerability vuln;
    vuln.query = query;
    vuln.vulnerable = false;

    if (usesTaintedInput) {
        if (!isParameterized(query)) {
            vuln.vulnerable = true;
            vuln.reason = "Tainted input used in non-parameterized SQL query";
        } else if (hasStringConcatenation(query)) {
            vuln.vulnerable = true;
            vuln.reason = "String concatenation detected in SQL query with tainted input";
        }
    }

    return vuln;
}

}  // namespace aegis::security
