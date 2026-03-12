#include <cassert>
#include <iostream>

#include "../compiler/semantic/type.hpp"

using namespace aegis;

void test_primitive_types() {
    auto int_type = makeIntType();
    auto float_type = makeFloatType();
    auto bool_type = makeBoolType();
    auto string_type = makeStringType();

    assert(int_type->toString() == "int");
    assert(float_type->toString() == "float");
    assert(bool_type->toString() == "bool");
    assert(string_type->toString() == "string");

    std::cout << "test_primitive_types passed\n";
}

void test_array_types() {
    auto int_array = makeArrayType(makeIntType());
    auto string_array = makeArrayType(makeStringType());

    assert(int_array->toString() == "array<int>");
    assert(string_array->toString() == "array<string>");

    std::cout << "test_array_types passed\n";
}

void test_map_types() {
    auto string_int_map = makeMapType(makeStringType(), makeIntType());
    auto int_string_map = makeMapType(makeIntType(), makeStringType());

    assert(string_int_map->toString() == "map<string, int>");
    assert(int_string_map->toString() == "map<int, string>");

    std::cout << "test_map_types passed\n";
}

void test_security_types() {
    auto tainted_string = makeTaintedType(makeStringType());
    auto safe_string = makeSafeType(makeStringType());

    assert(tainted_string->toString() == "tainted<string>");
    assert(safe_string->toString() == "safe<string>");

    std::cout << "test_security_types passed\n";
}

void test_type_equality() {
    auto int1 = makeIntType();
    auto int2 = makeIntType();
    auto float1 = makeFloatType();

    assert(int1->equals(int2.get()));
    assert(!int1->equals(float1.get()));

    auto arr1 = makeArrayType(makeIntType());
    auto arr2 = makeArrayType(makeIntType());
    auto arr3 = makeArrayType(makeStringType());

    assert(arr1->equals(arr2.get()));
    assert(!arr1->equals(arr3.get()));

    std::cout << "test_type_equality passed\n";
}

void test_nested_types() {
    // array<array<int>>
    auto nested_array = makeArrayType(makeArrayType(makeIntType()));
    assert(nested_array->toString() == "array<array<int>>");

    // map<string, array<int>>
    auto complex_map = makeMapType(makeStringType(), makeArrayType(makeIntType()));
    assert(complex_map->toString() == "map<string, array<int>>");

    // tainted<array<string>>
    auto tainted_array = makeTaintedType(makeArrayType(makeStringType()));
    assert(tainted_array->toString() == "tainted<array<string>>");

    std::cout << "test_nested_types passed\n";
}

int main() {
    test_primitive_types();
    test_array_types();
    test_map_types();
    test_security_types();
    test_type_equality();
    test_nested_types();

    std::cout << "All type system tests passed!\n";
    return 0;
}
