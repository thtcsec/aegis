#pragma once
#include <string>

namespace aegis::crypto {

std::string aes_encrypt(const std::string& data, const std::string& key);

}  // namespace aegis::crypto
