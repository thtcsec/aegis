#pragma once
#include <string>

namespace aegis::net {

class HttpClient {
public:
    HttpClient();
    std::string get(const std::string& url);
};

}  // namespace aegis::net
