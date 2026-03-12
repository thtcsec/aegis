#pragma once
#include <string>

namespace aegis::runtime {

class Capability {
public:
    Capability();
    bool check(const std::string& resource);
};

}  // namespace aegis::runtime
