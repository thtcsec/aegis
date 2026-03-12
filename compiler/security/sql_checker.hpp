#pragma once
#include <string>

namespace aegis::security {

struct SQLVulnerability {
    std::string query;
    bool vulnerable;
    std::string reason;
};

class SQLChecker {
public:
    SQLChecker();
    SQLVulnerability analyze(const std::string& query, bool usesTaintedInput);

private:
    bool isParameterized(const std::string& query) const;
    bool hasStringConcatenation(const std::string& query) const;
};

}  // namespace aegis::security
