
#include <string>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <functional>
#include <cassert>
#include <compare> // for <=>
#include <thread>
#include <optional>

//#include <concepts>
//#include <ranges>
//#include <numeric>


#include "ceto.h"


template <typename ceto__private__C1, typename ceto__private__C2>struct Generic : public ceto::enable_shared_from_this_base_for_templates {

    ceto__private__C1 x;

    int y;

    ceto__private__C2 z;

    explicit Generic(const ceto__private__C2 z, const ceto__private__C1 y) : x(y), y(99), z(z) {
    }

    Generic() = delete;

};

template <typename ceto__private__C3>struct GenericChild : public std::type_identity_t<decltype(Generic(std::declval<ceto__private__C3>(), std::vector {{1, 2, 3}}))> {

    explicit GenericChild(ceto__private__C3 x) : std::type_identity_t<decltype(Generic(std::declval<ceto__private__C3>(), std::vector {{1, 2, 3}}))> (std::move(x), std::vector {{1, 2, 3}}) {
    }

    GenericChild() = delete;

};

    auto main() -> int {
        const auto g = std::make_shared<const decltype(Generic{101, (-333)})>(101, (-333));
        const auto g2 = std::make_shared<const decltype(GenericChild{std::vector {{"x", "y", "z"}}})>(std::vector {{"x", "y", "z"}});
        ((std::cout << ceto::mado(g)->x) << ceto::mado(g)->y) << ceto::mado(g)->z;
        ((std::cout << ceto::maybe_bounds_check_access(ceto::mado(g2)->x,2)) << ceto::mado(g2)->y) << ceto::maybe_bounds_check_access(ceto::mado(g2)->z,1);
    }

