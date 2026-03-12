#pragma once
#include <string>

namespace aegis::net {

class Socket {
public:
    Socket();
    void connect(const std::string& host, int port);
};

}  // namespace aegis::net
