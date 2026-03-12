#include "vuln_detector.hpp"

namespace aegis::security {

VulnerabilityDetector::VulnerabilityDetector() {}

void VulnerabilityDetector::addVulnerability(VulnerabilityType type, const std::string& message,
                                             int line) {
    vulnerabilities_.push_back(Vulnerability{type, message, line});
}

std::vector<Vulnerability> VulnerabilityDetector::getVulnerabilities() const {
    return vulnerabilities_;
}

bool VulnerabilityDetector::hasVulnerabilities() const {
    return !vulnerabilities_.empty();
}

}  // namespace aegis::security
