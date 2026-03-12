#pragma once
#include <string>
#include <vector>

namespace aegis::security {

enum class VulnerabilityType {
    SQL_INJECTION,
    COMMAND_INJECTION,
    PATH_TRAVERSAL,
    XSS,
    BUFFER_OVERFLOW,
    USE_AFTER_FREE
};

struct Vulnerability {
    VulnerabilityType type;
    std::string message;
    int line;
};

class VulnerabilityDetector {
public:
    VulnerabilityDetector();

    void addVulnerability(VulnerabilityType type, const std::string& message, int line);
    std::vector<Vulnerability> getVulnerabilities() const;
    bool hasVulnerabilities() const;

private:
    std::vector<Vulnerability> vulnerabilities_;
};

}  // namespace aegis::security
