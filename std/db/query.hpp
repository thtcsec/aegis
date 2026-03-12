#pragma once
#include <string>

namespace aegis::db {

class Query {
public:
    Query();
    void execute(const std::string& sql);
};

}  // namespace aegis::db
