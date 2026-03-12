#pragma once
#include <string>

namespace aegis::db {

class Connection {
public:
    Connection();
    void connect(const std::string& connStr);
};

}  // namespace aegis::db
