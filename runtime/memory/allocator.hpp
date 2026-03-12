#pragma once
#include <cstddef>

namespace aegis::runtime {

class Allocator {
public:
    Allocator();
    void* allocate(size_t size);
};

}  // namespace aegis::runtime
